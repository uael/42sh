/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 13:39:06 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"
#include "ush/exp.h"
#include "ush/func.h"

typedef void	(t_evalcb)(t_ctx *ctx, t_tok *tok);

static t_evalcb	*g_eval[];

static inline int	ifclause(t_if *s)
{
	g_sh->child = 1;
	eval(&s->cond, s->ln);
	if (!g_sh->status)
		eval(&s->body, s->ln);
	else if (s->elsekind == ELSE_ELIF)
		return (ifclause(s->elsepart.elif));
	else if (s->elsekind == ELSE_ELSE)
		eval(&s->elsepart.body, s->ln);
	return (g_sh->status);
}

static inline void	ifclausedtor(t_if *s)
{
	if (s->elsekind == ELSE_ELIF)
		ifclausedtor(s->elsepart.elif);
	else if (s->elsekind == ELSE_ELSE)
		ft_deqdtor(&s->elsepart.body, NULL);
	ft_deqdtor(&s->cond, NULL);
	ft_deqdtor(&s->body, NULL);
	free(s->ln);
	free(s);
}

static inline void	pushuntilb(t_deq *dest, t_deq *src, char const *stop)
{
	t_tok	*tok;
	int		depth;

	depth = 0;
	while (!ft_strchr(stop, (tok = sh_toknext(src))->id) || depth)
	{
		if (tok->id == TOK_IF)
			++depth;
		else if (tok->id == TOK_FI)
			--depth;
		*(t_tok *)ft_deqpush(dest) = *tok;
	}
	(*(t_tok *)ft_deqpush(dest)).id = TOK_END;
}

static inline t_if	*ifclausector(t_deq *toks, char const *ln)
{
	t_if	*ifc;
	t_tok	*tok;

	ifc = ft_malloc(sizeof(t_if));
	ft_bzero(ifc, sizeof(t_if));
	ft_deqctor(&ifc->cond, sizeof(t_tok));
	pushuntilb(&ifc->cond, toks, (char []){TOK_THEN, '\0'});
	ft_deqctor(&ifc->body, sizeof(t_tok));
	pushuntilb(&ifc->body, toks, (char []){TOK_ELSE, TOK_ELIF, TOK_FI, '\0'});
	if ((tok = sh_tokpeek(toks))->id == TOK_ELSE)
	{
		ifc->elsekind = ELSE_ELSE;
		ft_deqctor(&ifc->elsepart.body, sizeof(t_tok));
		pushuntilb(&ifc->elsepart.body, toks, (char []){TOK_FI, '\0'});
		sh_toknext(toks);
	}
	else if (tok->id == TOK_ELIF)
	{
		ifc->elsekind = ELSE_ELIF;
		ifc->elsepart.elif = ifclausector(toks, ln);
	}
	else
		sh_toknext(toks);
	ifc->ln = ft_strdup(ln);
	return (ifc);
}


static void		evalif(t_ctx *ctx, t_tok *tok)
{
	t_if *ifc;

	(void)tok;
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	ifc = ifclausector(ctx->toks, ctx->ln);
	ps_procfn(ctx->proc, (t_proccb *)ifclause, (t_dtor)ifclausedtor, ifc);
	ctx->proc->child = 0;
}

static inline int		whileclause(t_while *s)
{
	g_sh->child = 1;
	eval(&s->cond, s->ln);
	while (!g_sh->status)
	{
		s->body.cur = 0;
		eval(&s->body, s->ln);
		s->cond.cur = 0;
		eval(&s->cond, s->ln);
	}
	return (g_sh->status);
}

static inline void		whileclausedtor(t_while *s)
{
	ft_deqdtor(&s->cond, NULL);
	ft_deqdtor(&s->body, NULL);
	free(s->ln);
	free(s);
}

static inline void		pushuntila(t_deq *dest, t_deq *src, char const *stop)
{
	t_tok	*tok;
	int		depth;

	depth = 0;
	while (!ft_strchr(stop, (tok = sh_toknext(src))->id) || depth)
	{
		if (tok->id == TOK_DO)
			++depth;
		else if (tok->id == TOK_DONE)
			--depth;
		*(t_tok *)ft_deqpush(dest) = *tok;
	}
	(*(t_tok *)ft_deqpush(dest)).id = TOK_END;
}

static inline t_while	*whileclausector(t_deq *toks, char const *ln)
{
	t_while	*whilec;

	whilec = ft_malloc(sizeof(t_while));
	ft_bzero(whilec, sizeof(t_while));
	ft_deqctor(&whilec->cond, sizeof(t_tok));
	pushuntila(&whilec->cond, toks, (char []){TOK_DO, '\0'});
	ft_deqctor(&whilec->body, sizeof(t_tok));
	pushuntila(&whilec->body, toks, (char []){TOK_DONE, '\0'});
	sh_toknext(toks);
	whilec->ln = ft_strdup(ln);
	return (whilec);
}

static void		evalwhile(t_ctx *ctx, t_tok *tok)
{
	t_while	*whilec;

	(void)tok;
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	whilec = whileclausector(ctx->toks, ctx->ln);
	ps_procfn(ctx->proc, (t_proccb *)whileclause, (t_dtor)whileclausedtor,
		whilec);
	ctx->proc->child = 0;
}

static uint8_t		g_end[] = {
	['('] = ')',
	['{'] = '}',
	[TOK_IF] = TOK_FI,
	[TOK_WHILE] = TOK_DONE,
};

static inline int	avcount(char *av[])
{
	int c;

	c = 0;
	while (*av++)
		++c;
	return (c);
}

static int			evalfn(t_proc *proc)
{
	t_func	*fn;
	char	*av0;
	char	*fname;

	av0 = g_sh->av[0];
	g_sh->av = proc->argv;
	g_sh->ac = avcount(proc->argv);
	g_sh->tty = 0;
	fname = g_sh->av[0];
	if (!(fn = sh_funcget(fname)))
		return (EXIT_FAILURE);
	g_sh->av[0] = av0;
	eval(&fn->body, fn->ln);
	g_sh->av[0] = fname;
	return (g_sh->status);
}

static void		evalfuncdef(t_ctx *ctx, t_tok *tok)
{
	t_tok		*beg;
	t_tok		*name;
	t_deq		body;
	char const	*id;
	int			depth;

	depth = 1;
	name = sh_toknext(ctx->toks);
	beg = sh_toknext(ctx->toks);
	ft_deqctor(&body, sizeof(t_tok));
	while ((tok = sh_toknext(ctx->toks)))
	{
		if (tok->id == beg->id)
			++depth;
		else if (tok->id == g_end[beg->id] && !--depth)
			break ;
		*(t_tok *)ft_deqpush(&body) = *tok;
	}
	sh_toknext(ctx->toks);
	id = ft_strndup(ctx->ln + name->pos, name->len);
	sh_funcset(id, &body, ctx->ln);
	free((void *)id);
}

static inline int	subshell(t_subshell *s)
{
	g_sh->child = 1;
	eval(&s->toks, s->ln);
	return (g_sh->status);
}

static inline void	subshelldtor(t_subshell *s)
{
	ft_deqdtor(&s->toks, NULL);
	free(s->ln);
	free(s);
}

static void		evalsubshell(t_ctx *ctx, t_tok *tok)
{
	int			depth;
	t_subshell	sh;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	ft_bzero(&sh, sizeof(t_subshell));
	ft_deqctor(&sh.toks, sizeof(t_tok));
	depth = 0;
	while ((tok = sh_toknext(ctx->toks))->id != ')' || depth)
	{
		if (tok->id == '(')
			++depth;
		else if (tok->id == ')')
			--depth;
		*(t_tok *)ft_deqpush(&sh.toks) = *tok;
	}
	sh_toknext(ctx->toks);
	(*(t_tok *)ft_deqpush(&sh.toks)).id = TOK_END;
	sh.ln = ft_strdup(ctx->ln);
	ps_procfn(ctx->proc, (t_proccb *)subshell, (t_dtor)subshelldtor,
		ft_memdup(&sh, sizeof(t_subshell)));
	ctx->proc->child = (t_bool)(g_sh->child ? 0 : 1);
}

static void		evalbracegrp(t_ctx *ctx, t_tok *tok)
{
	int			depth;
	t_subshell	sh;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	ft_bzero(&sh, sizeof(t_subshell));
	ft_deqctor(&sh.toks, sizeof(t_tok));
	depth = 0;
	while ((tok = sh_toknext(ctx->toks))->id != '}' || depth)
	{
		if (tok->id == '{')
			++depth;
		else if (tok->id == '}')
			--depth;
		*(t_tok *)ft_deqpush(&sh.toks) = *tok;
	}
	sh_toknext(ctx->toks);
	(*(t_tok *)ft_deqpush(&sh.toks)).id = TOK_END;
	sh.ln = ft_strdup(ctx->ln);
	ps_procfn(ctx->proc, (t_proccb *)subshell, (t_dtor)subshelldtor,
		ft_memdup(&sh, sizeof(t_subshell)));
	ctx->proc->child = 0;
}

static void		evalampr(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	(void)tok;
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf,
		STDOUT_FILENO, STDERR_FILENO, O_WRONLY | O_CREAT | O_TRUNC, 0
	};
	sh_toknext(ctx->toks);
}

static void		evalcmp(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDIN_FILENO, -1,
		O_RDWR | O_CREAT, 0
	};
	sh_toknext(ctx->toks);
}

static void		evalheredoc(t_ctx *ctx, t_tok *tok)
{
	int fd;

	(void)tok;
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	if (ctx->proc->in)
		free(ctx->proc->in);
	ctx->proc->in = NULL;
	fd = ft_isdigit(*(ctx->ln + tok->pos)) ? *(ctx->ln + tok->pos) - '0' : 0;
	tok = sh_toknext(ctx->toks);
	sh_toknext(ctx->toks);
	if (fd != 0)
		return ;
	ctx->proc->in = ft_strndup(ctx->ln + tok->pos, tok->len);
}

static void		evallamp(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 0;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDIN_FILENO, -1,
		O_RDONLY, 0
	};
	sh_toknext(ctx->toks);
}

static void		evalramp(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 0;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDOUT_FILENO, -1,
		O_WRONLY | O_CREAT | O_TRUNC, 0
	};
	sh_toknext(ctx->toks);
}

static void		evalraout(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDOUT_FILENO, -1,
		O_WRONLY | O_CREAT | O_APPEND, 0
	};
	sh_toknext(ctx->toks);
}

static void		evalrin(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDIN_FILENO, -1,
		O_RDONLY, 0
	};
	sh_toknext(ctx->toks);
}

static void		evalrout(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDOUT_FILENO, -1,
		O_WRONLY | O_CREAT | O_TRUNC, 0
	};
	sh_toknext(ctx->toks);
}

static char		**makeenv(t_map *vars, t_bool *owned)
{
	t_vec		*e;
	char		**envv;
	uint32_t	it;

	if (!(*owned = (t_bool)(vars->len > 0)))
		return (g_env);
	ft_vecctor(e = alloca(sizeof(t_vec)), sizeof(char *));
	envv = g_env;
	while (*envv)
		*(char **)ft_vecpush(e) = ft_strdup(*envv++);
	it = 0;
	while (it < vars->cap)
	{
		if (BUCKET_ISPOPULATED(vars->bucks, it))
		{
			ft_setenv(e, ((char **)vars->keys)[it], ((char **)vars->vals)[it]);
			ft_pfree((void **)&((char **)vars->vals)[it]);
			BUCKET_SET_ISDEL_TRUE(vars->bucks, it);
			--vars->len;
		}
		++it;
	}
	*(char **)ft_vecpush(e) = NULL;
	return (e->buf);
}

static void		makeargv(t_ctx *ctx, t_tok *tok, t_vec *av, t_bool c)
{
	while (tok)
		if (sh_tokis(tok, TOKS_WORD))
		{
			av && (!c || tok->id != TOK_DRBRA) ?
				sh_expwords(av, ctx->ln + tok->pos, tok->len) : 0;
			tok = sh_toknext(ctx->toks);
		}
		else if (sh_tokis(tok, TOKS_REDIR))
		{
			g_eval[tok->id](ctx, tok);
			tok = sh_tokpeek(ctx->toks);
		}
		else
			break ;
}

static void		evalword(t_ctx *ctx, t_tok *tok)
{
	t_bool	own;
	t_vec	av;
	char	*bin;

	ft_vecctor(&av, sizeof(char *));
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	while (!av.len)
		if (sh_tokis(tok, TOKS_REDIR))
		{
			g_eval[tok->id](ctx, tok);
			tok = sh_tokpeek(ctx->toks);
		}
		else if (sh_tokis(tok, TOKS_WORD))
		{
			sh_expwords(&av, ctx->ln + tok->pos, tok->len);
			tok = sh_toknext(ctx->toks);
		}
		else
			break ;
	bin = av.len ? ((char **)av.buf)[0] : "true";
	ctx->proc->envv = makeenv(&ctx->vars, &ctx->proc->ownenv);
	if (!(own = (t_bool)ft_strcmp("true", bin)) || !ft_strcmp("false", bin))
	{
		ft_vecdtor(&av, (t_dtor)ft_pfree);
		ps_procbit(ctx->proc, (t_bool)(own ? 1 : 0));
		return (makeargv(ctx, tok, NULL, 0));
	}
	if (sh_funcget(bin))
	{
		ctx->proc->kind = PROC_FN;
		ctx->proc->u.fn.cb = (t_proccb *)evalfn;
		ctx->proc->u.fn.dtor = NULL;
		ctx->proc->u.fn.data = NULL;
	}
	else
		ps_procexe(ctx->proc, "PATH", bin, ctx->proc->envv);
	makeargv(ctx, tok, &av, 0);
	*(char **)ft_vecpush(&av) = NULL;
	ctx->proc->argv = av.buf;
}

static void		evaltest(t_ctx *ctx, t_tok *tok)
{
	t_vec	av;
	char	*bin;

	ft_vecctor(&av, sizeof(char *));
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	tok = sh_toknext(ctx->toks);
	*(char **)ft_vecpush(&av) = ft_strdup("test");
	bin = ((char **)av.buf)[0];
	ctx->proc->envv = makeenv(&ctx->vars, &ctx->proc->ownenv);
	if (sh_funcget(bin))
	{
		ctx->proc->kind = PROC_FN;
		ctx->proc->u.fn.cb = (t_proccb *)evalfn;
		ctx->proc->u.fn.dtor = NULL;
		ctx->proc->u.fn.data = NULL;
	}
	else
		ps_procexe(ctx->proc, "PATH", bin, ctx->proc->envv);
	makeargv(ctx, tok, &av, 1);
	sh_toknext(ctx->toks);
	*(char **)ft_vecpush(&av) = NULL;
	ctx->proc->argv = av.buf;
}

static void		evalassign(t_ctx *ctx, t_tok *tok)
{
	char		*eq;
	char		*var;
	t_sds		val;
	uint32_t	it;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	sh_toknext(ctx->toks);
	eq = ft_strnchr(ctx->ln + tok->pos, '=', tok->len);
	var = ft_strndup(ctx->ln + tok->pos, eq - (ctx->ln + tok->pos));
	ft_sdsctor(&val);
	sh_expword(&val, eq + 1, tok->len - (eq - ctx->ln - tok->pos) - 1);
	!val.len ? (*ft_sdspush(&val) = '\0') : 0;
	ps_procbit(ctx->proc, 0);
	if (ft_mapget(&ctx->vars, var, &it))
	{
		free(var);
		free(((char **)ctx->vars.vals)[it]);
		((char **)ctx->vars.vals)[it] = val.buf;
	}
	else if (ft_mapput(&ctx->vars, var, &it))
		((char **)ctx->vars.vals)[it] = val.buf;
	else
	{
		free(var);
		free(val.buf);
	}
}

static void		evalbang(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_toknext(ctx->toks);
	ctx->job->bang = 1;
}

static int		evalexport(t_map *vars)
{
	uint32_t it;

	if (!vars->len)
		return (NOP);
	it = 0;
	while (it < vars->cap)
	{
		if (BUCKET_ISPOPULATED(vars->bucks, it))
		{
			sh_varset(((char **)vars->keys)[it], ((char **)vars->vals)[it]);
			ft_pfree((void **)&((char **)vars->vals)[it]);
			BUCKET_SET_ISDEL_TRUE(vars->bucks, it);
			--vars->len;
		}
		++it;
	}
	return (YEP);
}

static void		evalpipe(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
	ps_procctor(ctx->proc);
}

static void		evaland(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	ctx->job->next = ft_malloc(sizeof(t_job));
	ctx->job->andor = ANDOR_AND;
	ps_jobctor(ctx->job->next);
	ctx->job = ctx->job->next;
	ctx->proc = NULL;
}

static void		evalor(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	ctx->job->next = ft_malloc(sizeof(t_job));
	ctx->job->andor = ANDOR_OR;
	ps_jobctor(ctx->job->next);
	ctx->job = ctx->job->next;
	ctx->proc = NULL;
}

static void		evalsemicolon(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_toknext(ctx->toks);
	if (!ctx->root->procs.len)
		return ;
	evalexport(&ctx->vars);
	g_sh->status = ps_joblaunch(ctx->root, 1);
	ps_jobctor(ctx->root);
	ctx->proc = NULL;
}

static void		evalampersand(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	g_sh->status = ps_joblaunch(ps_poolpush(ctx->root), 0);
	ps_jobctor(ctx->root);
	ctx->proc = NULL;
}

static t_evalcb	*g_eval[] = {
	[TOK_IF] = evalif,
	[TOK_WHILE] = evalwhile,
	[TOK_FUNCTION] = evalfuncdef,
	[TOK_AMPR] = evalampr,
	[TOK_CMP] = evalcmp,
	[TOK_HEREDOC] = evalheredoc,
	[TOK_LAMP] = evallamp,
	[TOK_RAMP] = evalramp,
	[TOK_RAOUT] = evalraout,
	[TOK_WORD] = evalword,
	[TOK_DLBRA] = evaltest,
	[TOK_ASSIGN] = evalassign,
	[TOK_LAND] = evaland,
	[TOK_LOR] = evalor,
	['!'] = evalbang,
	['('] = evalsubshell,
	['{'] = evalbracegrp,
	['<'] = evalrin,
	['>'] = evalrout,
	['|'] = evalpipe,
	[';'] = evalsemicolon,
	['\n'] = evalsemicolon,
	['\0'] = evalsemicolon,
	['&'] = evalampersand,
};

void		eval(t_deq *toks, char const *ln)
{
	t_ctx	ctx;
	t_tok	*tok;
	t_job	job;

	ft_bzero(&ctx, sizeof(t_ctx));
	ps_jobctor(ctx.root = &job);
	ft_mapctor(&ctx.vars, g_strhash, sizeof(char *), sizeof(char *));
	ctx.job = ctx.root;
	ctx.ln = ln;
	ctx.stop = toks->len;
	ctx.toks = toks;
	while (ctx.toks->cur < ctx.stop && ctx.toks->cur < ctx.toks->len)
	{
		tok = ft_deqbeg(ctx.toks);
		g_eval[tok->id](&ctx, tok);
		if (tok->id == TOK_END)
			break ;
	}
	ps_jobdtor(ctx.root);
	ft_mapdtor(&ctx.vars, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
}

#define UNEX "syntax error: Unexpected token `%s'"

static inline int	evalfini(int ret, t_deq *toks)
{
	
	t_tok	*tok;

	if (ret > 0)
	{
		tok = sh_tokpeek(toks);
		while (tok)
			if (tok->id != TOK_EOL && tok->id != TOK_END)
				tok = sh_toknext(toks);
			else
			{
				sh_toknext(toks);
				break ;
			}
	}
	toks->cur = toks->len;
	return (ret ? NOP : YEP);
}

inline int			sh_eval(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	int		st;

	st = 0;
	while (!st)
	{
		sh_evallinebreak(toks);
		if (!sh_tokpeek(toks))
			return (evalfini(YEP, toks));
		if ((st = sh_evallist(fd, toks, ln)) == OUF)
			return (evalfini(OUF, toks));
		if (!(tok = sh_tokpeek(toks)) || tok->id == TOK_END)
			return (evalfini(YEP, toks));
	}
	tok = sh_tokpeek(toks);
	return (evalfini(sh_evalerr(*ln, tok, UNEX, sh_tokstr(tok)), toks));
}
