// Scott Kuhl
//
// This program does not check the return code of close(), dup2(),
// execlp(), fork(), and waitpid(). A good program would add those
// additional checks!
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

typedef struct	s_job
{
	int 	ac;
	char	**av;
	char	**env;
	pid_t	pid;
	int		status;
	int		read[2];
	int		write[2];
}				t_job;

void	job_ctor(t_job *self, int ac, char **av, char **env)
{
	memset(self, 0, sizeof(t_job));
	self->ac = ac;
	self->av = av;
	self->env = env;
}

int		job_run(t_job *self, int *read)
{
	pid_t pid;

	pipe(self->write);
	if (read)
		memcpy(self->read, read, 2 * sizeof(int));
	pid = fork();
	if (pid == 0)
	{
		close(self->write[READ_END]);
		dup2(self->write[WRITE_END], STDOUT_FILENO);
		if (self->read[0])
		{
			close(self->read[WRITE_END]);
			dup2(self->read[READ_END], STDIN_FILENO);
		}
		execve(self->av[0], self->av, self->env);
		return (1);
	}
	self->pid = pid;
	if (self->read[0])
	{
		close(self->read[WRITE_END]);
		close(self->read[READ_END]);
	}
	return (0);
}

void	job_finalize(t_job *self)
{
	close(self->write[READ_END]);
	close(self->write[WRITE_END]);
	waitpid(self->pid, &self->status, 0);
}

pid_t do_exec(char **cmd, int *write, int *read)
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
		execv(cmd[0], cmd);
		exit(EXIT_FAILURE);
	}
	return pid;
}

int do_pipes(char ***cmds)
{
	int status;
	char	***cmd;
	int 	c[2];
	int 	d[2];
	int 	*p;
	pid_t	pid;

	p = NULL;
	cmd = cmds - 1;
	status = 0;
	while (*++cmd)
		if (!*(cmd + 1))
		{
			pid = do_exec(*cmd, NULL, p);
			if (p)
			{
				close(p[READ_END]);
				close(p[WRITE_END]);
			}
			waitpid(pid, &status, 0);
		}
		else
		{
			pipe(c);
			do_exec(*cmd, c, p);
			if (p)
			{
				close(p[READ_END]);
				close(p[WRITE_END]);
			}
			p = memcpy(d, c, 2 * sizeof(int));
		}
	return (status);
}

int do_pipe(char **a, char **b, char **c)
{
	int fd1[2];
	int fd2[2];
	int status;
	pid_t child3;

	pipe(fd1);
	do_exec(a, fd1, NULL);
	pipe(fd2);
	do_exec(b, fd2, fd1);
	close(fd1[READ_END]);
	close(fd1[WRITE_END]);
	child3 = do_exec(c, NULL, fd2);
	close(fd2[READ_END]);
	close(fd2[WRITE_END]);
	waitpid(child3, &status, 0);
	return 0;
}

int main(void)
{
	t_job jobs[3];

	job_ctor(jobs, 4,
		(char *[5]) {"/bin/ls", "-la", "foo", "include", NULL},
		(char *[1]){NULL}
	);
	job_ctor(jobs + 1, 3,
		(char *[5]) {"/usr/bin/grep", "--color=always", "alucas-", NULL},
		(char *[1]){NULL}
	);
	job_ctor(jobs + 2, 3,
		(char *[5]) {"/usr/bin/grep", "--color=always", "2017_paris", NULL},
		(char *[1]){NULL}
	);
	job_run(jobs, NULL);
	job_run(jobs + 1, jobs[0].write);
	job_run(jobs, NULL);
	job_run(jobs + 2, jobs[1].write);.

}