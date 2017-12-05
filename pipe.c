#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libft.h>

#define READ_END 0
#define WRITE_END 1

typedef enum	e_job_kind
{
	JOB_NONE,
	JOB_OR,
	JOB_AND,
	JOB_PIPE,
	JOB_REDIRECT_IN,
	JOB_REDIRECT_OUT,
	JOB_REDIRECT_APPEND_IN,
	JOB_REDIRECT_APPEND_OUT
}				t_job_kind;

typedef struct	s_job
{
	t_job_kind	kind;
	char		**av;
	char		**env;
	pid_t		pid;
	int			status;
}				t_job;

void			job_ctor(t_job *self, char **av, char **env)
{
	FT_INIT(self, t_job);
	self->av = av;
	self->env = env;
}

int				job_run(t_job *self, int *write, int *read)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (write)
		{
			close(write[READ_END]);
			dup2(write[WRITE_END], STDOUT_FILENO);
		}
		if (read)
		{
			close(read[WRITE_END]);
			dup2(read[READ_END], STDIN_FILENO);
		}
		execve(self->av[0], self->av, self->env);
		return (1);
	}
	self->pid = pid;
	return (0);
}

typedef t_vec	t_worker;

void			ft_worker_ctor(t_worker *jobs)
{
	ft_vec_ctor(jobs, sizeof(t_vec));
}

t_job			*ft_worker_push(t_worker *jobs, t_job *job, t_job_kind next)
{
	job->kind = next;
	return ((t_job *)ft_vec_pushc(jobs, job));
}

int				ft_worker_run(t_worker *jobs)
{
	t_job	*it;
	int 	c[2];
	int 	d[2];
	int 	*p;

	p = NULL;
	it = (t_job *)ft_vec_begin(jobs) - 1;
	while (++it != (t_job *)ft_vec_end(jobs))
	{
		if (it->kind == JOB_PIPE)
		{
			pipe(c);
			job_run(it, c, p);
			p ? (void)(close(p[READ_END]) & close(p[WRITE_END])) : 0;
			p = memcpy(d, c, 2 * sizeof(int));
		}
		else if (it->kind == JOB_NONE)
		{
			job_run(it, NULL, p);
			p ? (void)(close(p[READ_END]) & close(p[WRITE_END])) : 0;
		}
		waitpid(it->pid, &it->status, 0);
	}
	return (0);
}

int main(void)
{
	t_worker	worker;
	t_job		job1;
	t_job		job2;
	t_job		job3;

	ft_worker_ctor(&worker);
	job_ctor(&job1,
		(char *[5]) {"/bin/ls", "-la", "foo", "include", NULL},
		(char *[1]){NULL}
	);
	job_ctor(&job2,
		(char *[5]) {"/usr/bin/grep", "--color=always", "alucas-", NULL},
		(char *[1]){NULL}
	);
	job_ctor(&job3,
		(char *[5]) {"/usr/bin/grep", "--color=always", "2017_paris", NULL},
		(char *[1]){NULL}
	);
	ft_worker_push(&worker, &job1, JOB_PIPE);
	ft_worker_push(&worker, &job2, JOB_PIPE);
	ft_worker_push(&worker, &job3, JOB_NONE);
	return (ft_worker_run(&worker));
}