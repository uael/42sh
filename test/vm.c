#include <libft.h>
#include <wait.h>

# define OP_MAX UINT16_MAX
# define OP_LOCK (1 << 1)
# define OP_EXEC (1 << 2)

enum e_op
{
	OP_BIN = 0,
	OP_ARG,
	OP_JUMP,
	OP_TERM
};

typedef struct	s_op
{
	uint8_t		kind;
	uint8_t		flags;
	uint16_t	pos;
	uint16_t	len;
	uint16_t	jump;
}				t_op;

typedef int		(t_opc)(t_op *op, t_vec *av, t_vec *env, char *ln);

static t_op		g_ops[OP_MAX];
static int		g_st = 0;

static int		vm_evalbin(t_op *op, t_vec *av, t_vec *env, char *ln);
static int		vm_evalarg(t_op *op, t_vec *av, t_vec *env, char *ln);
static int		vm_evalterm(t_op *op, t_vec *av, t_vec *env, char *ln);
static int		vm_evaljump(t_op *op, t_vec *av, t_vec *env, char *ln);

static int		vm_eval(t_op *op, t_vec *av, t_vec *env, char *ln)
{
	static t_opc	*opc[OP_TERM + 1] = {
		[OP_BIN] = vm_evalbin,
		[OP_ARG] = vm_evalarg,
		[OP_TERM] = vm_evalterm,
		[OP_JUMP] = vm_evaljump,
	};
	return (opc[op->kind](op, av, env, ln));
}

static int		vm_evalbin(t_op *op, t_vec *av, t_vec *env, char *ln)
{
	pid_t	pid;
	t_vec	nav;
	
	(void)env;
	(void)av;
	ft_vecctor(&nav, sizeof(char *));
	while (!nav.len)
		if ((op->flags & OP_LOCK))
		{
			*(char **)ft_vecpush(&nav) = ft_strndup(ln + op->pos, op->len);
			++op;
		}
		else
		{
			//sh_wordexplode(&nav, ln + op->pos, op->len);
			*(char **)ft_vecpush(&nav) = ft_strndup(ln + op->pos, op->len);
			if (!nav.len && ++op->kind != OP_ARG)
			{
				g_st = 0;
				return (vm_eval(op, &nav, env, ln));
			}
		}
	if (!ft_strcmp(*(char **)nav.buf, "true"))
	{
		g_st = 0;
		ft_vecdtor(&nav, (t_dtor)ft_pfree);
		return (vm_eval(g_ops + --op->jump, av, env, ln));
	}
	if (!ft_strcmp(*(char **)nav.buf, "fals"))
	{
		g_st = 1;
		ft_vecdtor(&nav, (t_dtor)ft_pfree);
		--op;
		return (vm_eval(g_ops + op->jump, av, env, ln));
	}
	if (((pid = fork()) == 0))
		return (vm_eval(op, &nav, env, ln));
	waitpid(pid, &g_st, WUNTRACED);
	if (WIFEXITED(g_st))
		g_st = WEXITSTATUS(g_st);
	return (vm_eval(g_ops + op->jump, &nav, env, ln));
}

static int		vm_evalarg(t_op *op, t_vec *av, t_vec *env, char *ln)
{
	if ((op->flags & OP_LOCK))
		*(char **)ft_vecpush(av) = ft_strndup(ln + op->pos, op->len);
	else
	{
		//sh_wordexplode(av, ln + op->pos, op->len);
		*(char **)ft_vecpush(av) = ft_strndup(ln + op->pos, op->len);
	}
	return (vm_eval(++op, av, env, ln));
}

static int		vm_evaljump(t_op *op, t_vec *av, t_vec *env, char *ln)
{
	if (!g_st)
		return (vm_eval(op + op->jump, av, env, ln));
	return (vm_eval(++op, av, env, ln));
}

static int		vm_evalterm(t_op *op, t_vec *av, t_vec *env, char *ln)
{
	(void)op;
	(void)env;
	(void)ln;
	if ((op->flags & OP_EXEC) && av && av->len)
	{
		execv(*(char **)av->buf, (char **)av->buf);
		exit(1);
	}
	if (op->jump)
		return (vm_eval(g_ops + op->jump, av, env, ln));
	return (g_st);
}

int main(void)
{
	g_ops[0] = (t_op){OP_BIN,OP_LOCK,0,7,4};
	g_ops[1] = (t_op){OP_ARG,OP_LOCK,8,2,4};
	g_ops[2] = (t_op){OP_ARG,OP_LOCK,11,2,4};
	g_ops[3] = (t_op){OP_TERM,OP_EXEC,13,1,4};
	g_ops[4] = (t_op){OP_BIN,OP_LOCK,18,4,6};
	g_ops[5] = (t_op){OP_TERM,OP_LOCK,19,1,8};
	g_ops[6] = (t_op){OP_JUMP,0,24,4,8};
	g_ops[7] = (t_op){OP_TERM,0,13,1,11};
	g_ops[8] = (t_op){OP_BIN,OP_LOCK,29,7,11};
	g_ops[9] = (t_op){OP_ARG,OP_LOCK,37,1,11};
	g_ops[10] = (t_op){OP_TERM,OP_EXEC,38,1,11};
	g_ops[11] = (t_op){OP_TERM,0,13,1,0};

	return (vm_eval(g_ops, NULL, NULL, "/bin/ls -a -l; if fals; then /bin/ls a; fi"));
}
