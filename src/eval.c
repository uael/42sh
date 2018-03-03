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

static void		evalif(t_ctx *ctx, t_tok *tok)
{
	(void)ctx;
	(void)tok;
}

static void		evalwhile(t_ctx *ctx, t_tok *tok)
{
	(void)ctx;
	(void)tok;
}

static void		evalfuncdef(t_ctx *ctx, t_tok *tok)
{
	(void)ctx;
	(void)tok;
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

static void		makeargv(t_ctx *ctx, t_tok *tok, t_vec *av)
{
	while (tok)
		if (sh_tokis(tok, TOKS_WORD))
		{
			av ? sh_expwords(av, ctx->ln + tok->pos, tok->len) : 0;
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
		return (makeargv(ctx, tok, NULL));
	}
	if (sh_funcget(bin))
	{
		ctx->proc->kind = PROC_FN;
		ctx->proc->u.fn.cb = (t_proccb *)sh_evalfn;
		ctx->proc->u.fn.dtor = NULL;
		ctx->proc->u.fn.data = NULL;
	}
	else
		ps_procexe(ctx->proc, "PATH", bin, ctx->proc->envv);
	makeargv(ctx, tok, &av);
	*(char **)ft_vecpush(&av) = NULL;
	ctx->proc->argv = av.buf;
}

static void		evaltest(t_ctx *ctx, t_tok *tok)
{
	(void)ctx;
	(void)tok;
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
	ctx->scope = 0;
	evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
	ps_procctor(ctx->proc);
}

static void		evaland(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	ctx->scope = 0;
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
	ctx->scope = 0;
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
	ctx->scope = 0;
	evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	g_sh->status = ps_joblaunch(ctx->root, 1);
	ps_jobctor(ctx->root);
	ctx->proc = NULL;
}

static void		evalampersand(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	ctx->scope = 0;
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
