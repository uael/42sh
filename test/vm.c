#include <libft.h>
#include <sys/wait.h>
#include <term.h>
#include <printf.h>

# ifndef CHILD_MAX
#  define CHILD_MAX 266
# endif
# define AV_MAX UINT16_MAX
# define OP_MAX UINT16_MAX
# define OP_LOCK (1 << 1)
# define OP_EXEC (1 << 2)
# define OP_FJMP (1 << 3)
# define OP_BG (1 << 5)
# define OP_BEG (1 << 6)
# define OP_END (1 << 7)

enum e_op
{
	OP_BIN = 0,
	OP_ARG,
	OP_JUMP,
	OP_TERM,
	OP_WAIT,
	OP_PIPE,
	OP_FORK,
};

enum e_proc
{
	PROC_COMPLETED = 0,
	PROC_STOPPED,
	PROC_RUNNING,
	PROC_CONTINUED
};

typedef struct	s_op
{
	uint8_t		kind;
	uint8_t		flags;
	uint16_t	pos;
	uint16_t	len;
	uint16_t	jump;
}				t_op;

typedef struct	s_proc2
{
	pid_t		pid;
	uint8_t		state;
	uint8_t		status;
}				t_proc2;

typedef struct	s_pipeline
{
	t_proc2		*beg;
	t_proc2		*end;
}				t_pipeline;

typedef struct	s_job2
{
	pid_t		pgid;
	t_pipeline	pipeline;
}				t_job2;

typedef int		(t_opc)(t_op *op, char *ln);
typedef int		(t_bic)(int ac, char *av[], char *ev[]);

static t_op		g_op[OP_MAX];
static char		*g_av[AV_MAX];
static t_proc2	g_ch[CHILD_MAX];
static t_job2	g_bg[CHILD_MAX];
static t_job2	g_fg;
static t_bic	*g_bi = NULL;
//static int		g_oc = 0;
static int		g_ac = 0;
static int		g_cc = 0;
static int		g_bc = 0;
static int		g_st = 0;
static int		g_pipe[2] = {0, 0};
static int		g_io[3] = {0, 0, 0};
static t_map	g_builtins = {
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(t_bic *), NULL, NULL
};
static t_map	g_binaries = {
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(char *), NULL, NULL
};

extern int		sh_bicd(int ac, char **av, char **env);
extern int		sh_biecho(int ac, char **av, char **env);

static int		vm_evalbin(t_op *o, char *ln);
static int		vm_evalarg(t_op *o, char *ln);
static int		vm_evalterm(t_op *op, char *ln);
static int		vm_evaljump(t_op *op, char *ln);
static int		vm_evalwait(t_op *op, char *ln);
static int		vm_evalpipe(t_op *op, char *ln);
static int		vm_evalfork(t_op *op, char *ln);

static int		vm_eval(t_op *op, char *ln)
{
	static t_opc	*opc[] = {
		[OP_BIN] = vm_evalbin,
		[OP_ARG] = vm_evalarg,
		[OP_TERM] = vm_evalterm,
		[OP_JUMP] = vm_evaljump,
		[OP_WAIT] = vm_evalwait,
		[OP_PIPE] = vm_evalpipe,
		[OP_FORK] = vm_evalfork,
	};
	static char		*opn[] = {
		[OP_BIN] = "OP_BIN",
		[OP_ARG] = "OP_ARG",
		[OP_TERM] = "OP_TERM",
		[OP_JUMP] = "OP_JUMP",
		[OP_WAIT] = "OP_WAIT",
		[OP_PIPE] = "OP_PIPE",
		[OP_FORK] = "OP_FORK",
	};
	dprintf(1, "%d -> [%zu]{%s, %d, %d, %d, %d} -> '%s'\n", g_st, op - g_op,
		opn[op->kind], op->flags, op->pos, op->len, op->jump,
		ft_strncpy(alloca(op->len + 1), ln + op->pos, op->len));
	return (opc[op->kind](op, ln));
}

static int		vm_evalfork(t_op *o, char *ln)
{
	pid_t		pid;
	t_job2		*job;

	if ((o->flags & OP_BG))
		job = g_bg + ((o->flags & OP_BEG) ? g_bc++ : g_bc - 1);
	else
		job = &g_fg;
	if ((o->flags & OP_BEG))
	{
		job->pipeline.beg = g_ch + g_cc++;
		job->pipeline.end = job->pipeline.beg;
		job->pgid = 0;
	}
	else
		job->pipeline.end = g_ch + g_cc++;
	job->pipeline.end->state = PROC_RUNNING;
	job->pipeline.end->status = 0;
	if ((!g_bi || g_io[STDOUT_FILENO] != STDOUT_FILENO) && (pid = fork()) > 0)
	{
		job->pipeline.end->pid = pid;
		setpgid(pid, job->pgid);
		if (!job->pgid)
			job->pgid = pid;
		return (vm_eval(g_op + o->jump, ln));
	}
	return (vm_eval(++o, ln));
}

static int		vm_evalpipe(t_op *op, char *ln)
{
	if ((op->flags & OP_END))
	{
		g_pipe[0] = 0;
		g_pipe[1] = 0;
		g_io[STDOUT_FILENO] = STDOUT_FILENO;
	}
	else
	{
		if ((op->flags & OP_BEG))
			ft_memcpy(g_io, STD_FILENOS, 3 * sizeof(int));
		else
		{
			if (g_io[STDIN_FILENO] != STDIN_FILENO)
				close(g_io[STDIN_FILENO]);
			if (g_io[STDOUT_FILENO] != STDOUT_FILENO)
				close(g_io[STDOUT_FILENO]);
			g_io[STDIN_FILENO] = g_pipe[0];
		}
		if (pipe(g_pipe) < 0)
			exit(1);
		g_io[STDOUT_FILENO] = g_pipe[1];
	}
	return (vm_eval(++op, ln));
}

static int		vm_evalbin(t_op *o, char *ln)
{
	uint32_t	it;

	g_ac = 0;
	while (!g_ac)
		if ((o->flags & OP_LOCK))
		{
			g_av[g_ac++] = ft_strncpy(alloca(o->len + 1), ln + o->pos, o->len);
			++o;
		}
		else
		{
			//sh_wordexplode(&nav, ln + op->pos, op->len);
			g_av[g_ac++] = ft_strncpy(alloca(o->len + 1), ln + o->pos, o->len);
			if (!g_ac && ++o->kind != OP_ARG)
			{
				g_st = 0;
				return (vm_eval(o, ln));
			}
		}
	--o;
	if (!ft_strcmp(*g_av, "true"))
	{
		g_st = 0;
		--g_ac;
		return (vm_eval(g_op + o->jump, ln));
	}
	if (!ft_strcmp(*g_av, "fals"))
	{
		g_st = 1;
		--g_ac;
		return (vm_eval(g_op + o->jump, ln));
	}
	g_bi = NULL;
	if (ft_mapget(&g_builtins, *g_av, &it))
		g_bi = ((t_bic **)g_builtins.vals)[it];
	return (vm_eval(++o, ln));
}

static int		vm_evalarg(t_op *o, char *ln)
{
	if ((o->flags & OP_LOCK))
		g_av[g_ac++] = ft_strncpy(alloca(o->len + 1), ln + o->pos, o->len);
	else
	{
		//sh_wordexplode(av, ln + op->pos, op->len);
		g_av[g_ac++] = ft_strncpy(alloca(o->len + 1), ln + o->pos, o->len);
	}
	return (vm_eval(++o, ln));
}

static int		vm_evaljump(t_op *op, char *ln)
{
	if ((op->flags & OP_FJMP) || !g_st)
		return (vm_eval(g_op + op->jump, ln));
	return (vm_eval(++op, ln));
}

extern char **environ;

static int		vm_evalterm(t_op *op, char *ln)
{
	uint32_t	it;
	pid_t		pid;
	int			status;
	t_proc2		*p;

	(void)op;
	(void)ln;
	if ((op->flags & OP_EXEC) && g_ac)
	{
		g_pipe[0] != STDIN_FILENO && g_pipe[0] != g_io[0]
			? close(g_pipe[0]) : 0;
		ft_dup2std(g_io, STD_FILENOS);
		g_av[g_ac] = NULL;
		if (g_bi)
			g_st = g_bi(g_ac, g_av, environ);
		else
		{
			if (ft_mapget(&g_binaries, *g_av, &it))
				*g_av = ((char **)g_builtins.vals)[it];
			execve(*g_av, g_av, environ);
			exit(1);
		}
		g_bi = NULL;
		g_ac = 0;
	}
	else if (!(op->flags & OP_EXEC) && g_fg.pgid)
	{
		while (1)
		{
			while ((pid = waitpid(-g_fg.pgid, &status, WUNTRACED)) < 0)
				if (errno != EINTR)
					break ;
			p = g_fg.pipeline.beg;
			while (p <= g_fg.pipeline.end)
			{
				if (pid == p->pid && p->state != PROC_COMPLETED)
				{
					p->state = PROC_COMPLETED;
					p->status = (uint8_t)WEXITSTATUS(status);
					break ;
				}
				++p;
			}
			if (p > g_fg.pipeline.end)
				break ;
		}
	}
	if (op->jump)
		return (vm_eval(g_op + op->jump, ln));
	return (g_st);
}

static int		vm_evalwait(t_op *op, char *ln)
{
	pid_t		pid;
	int			status;
	t_proc2		*p;

	if (g_fg.pgid)
	{
		while (1)
		{
			while ((pid = waitpid(-g_fg.pgid, &status, WUNTRACED)) < 0)
				if (errno != EINTR)
					break ;
			p = g_fg.pipeline.beg;
			while (p <= g_fg.pipeline.end)
			{
				if (pid == p->pid && p->state != PROC_COMPLETED)
				{
					p->state = PROC_COMPLETED;
					p->status = (uint8_t)WEXITSTATUS(status);
					break ;
				}
				++p;
			}
			if (p > g_fg.pipeline.end)
				break ;
		}
	}
	if (op->jump)
		return (vm_eval(g_op + op->jump, ln));
	return (g_st);
}

int main(void)
{
	uint32_t it;

	if (ft_mapput(&g_builtins, "cd", &it))
		((t_bic **)g_builtins.vals)[it] = sh_bicd;
	if (ft_mapput(&g_builtins, "echo", &it))
		((t_bic **)g_builtins.vals)[it] = sh_biecho;
	if (ft_mapput(&g_binaries, "pwd", &it))
		((char **)g_builtins.vals)[it] = "/bin/pwd";
	if (ft_mapput(&g_binaries, "ls", &it))
		((char **)g_builtins.vals)[it] = "/bin/ls";
	if (ft_mapput(&g_binaries, "sleep", &it))
		((char **)g_builtins.vals)[it] = "/bin/sleep";
	if (ft_mapput(&g_binaries, "wc", &it))
		((char **)g_builtins.vals)[it] = "/usr/bin/wc";

	/*g_op[0] = (t_op){OP_BIN,OP_LOCK,0,3,2};
	g_op[1] = (t_op){OP_TERM,OP_EXEC,0,0,2};
	g_op[2] = (t_op){OP_JUMP,OP_LOCK,4,2,4};
	g_op[3] = (t_op){OP_TERM,0,0,0,11};
	g_op[4] = (t_op){OP_BIN,OP_LOCK,7,2,6};
	g_op[5] = (t_op){OP_ARG,OP_LOCK,10,2,0};
	g_op[6] = (t_op){OP_TERM,OP_EXEC,0,0,7};
	g_op[7] = (t_op){OP_JUMP,OP_LOCK,13,2,9};
	g_op[8] = (t_op){OP_TERM,0,0,0,11};
	g_op[9] = (t_op){OP_BIN,OP_LOCK,16,3,10};
	g_op[10] = (t_op){OP_TERM,OP_EXEC,0,0,11};
	g_op[11] = (t_op){OP_TERM,0,0,0,0};

	vm_eval(g_op, "pwd && cd .. && pwd");*/

	g_op[0] = (t_op){OP_BIN,OP_LOCK|OP_BEG,6,5,3};
	g_op[1] = (t_op){OP_ARG,OP_LOCK,12,1,0};
	g_op[2] = (t_op){OP_TERM,OP_EXEC,0,0,3};
	g_op[3] = (t_op){OP_WAIT,0,0,0,4};
	g_op[4] = (t_op){OP_JUMP,0,0,0,6};
	g_op[5] = (t_op){OP_TERM,0,0,0,12};
	g_op[6] = (t_op){OP_BIN,OP_LOCK|OP_BEG|OP_PIPE,18,2,8};
	g_op[7] = (t_op){OP_TERM,OP_EXEC,0,0,10};
	g_op[8] = (t_op){OP_BIN,OP_LOCK,23,2,10};
	g_op[9] = (t_op){OP_TERM,OP_EXEC,0,0,10};
	g_op[10] = (t_op){OP_WAIT,0,0,0,11};
	g_op[11] = (t_op){OP_JUMP,OP_FJMP,0,0,0};
	g_op[12] = (t_op){OP_TERM,0,0,0,0};

	return vm_eval(g_op, "while sleep 1; do ls | wc; done");
}
