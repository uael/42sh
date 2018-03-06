/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/alias.h"
#include "ush/eval.h"
#include "ush/exp.h"
#include "ush/func.h"

static char	**makeenv(t_map *vars, t_bool *owned)
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
		if (!(vars->bucks[it] & BUCKET_BOTH))
		{
			ft_setenv(e, ((char **)vars->keys)[it], ((char **)vars->vals)[it]);
			ft_pfree((void **)&((char **)vars->vals)[it]);
			vars->bucks[it] |= BUCKET_DELETED;
			--vars->len;
		}
		++it;
	}
	*(char **)ft_vecpush(e) = NULL;
	return (e->buf);
}

static void	makeargv(t_ctx *ctx, t_tok *tok, t_vec *av, t_bool c)
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

static char	*evalbin(t_ctx *ctx, t_tok *tok, t_vec *av)
{
	char *alias;

	ft_vecctor(av, sizeof(char *));
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	while (!av->len)
		if (sh_tokis(tok, TOKS_REDIR))
		{
			g_eval[tok->id](ctx, tok);
			tok = sh_tokpeek(ctx->toks);
		}
		else if (sh_tokis(tok, TOKS_WORD))
		{
			sh_expwords(av, ctx->ln + tok->pos, tok->len);
			tok = sh_toknext(ctx->toks);
		}
		else
			break ;
	if (!av->len)
		return ("true");
	return ((alias = sh_aliasget(((char **)av->buf)[0])) ?
		sh_evalalias(ctx, tok, av, alias) : ((char **)av->buf)[0]);
}

inline void	sh_evalword(t_ctx *ctx, t_tok *tok)
{
	t_bool	own;
	t_vec	av;
	char	*bin;

	bin = evalbin(ctx, tok, &av);
	ctx->proc->envv = makeenv(&ctx->vars, &ctx->proc->ownenv);
	if (!(own = (t_bool)ft_strcmp("true", bin)) || !ft_strcmp("false", bin))
	{
		ft_vecdtor(&av, (t_dtor)ft_pfree);
		ps_procbit(ctx->proc, (t_bool)(own ? 1 : 0));
		return (makeargv(ctx, sh_tokpeek(ctx->toks), NULL, 0));
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
	makeargv(ctx, sh_tokpeek(ctx->toks), &av, 0);
	*(char **)ft_vecpush(&av) = NULL;
	ctx->proc->argv = av.buf;
}

inline void	sh_evaltest(t_ctx *ctx, t_tok *tok)
{
	t_vec	av;

	ft_vecctor(&av, sizeof(char *));
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	tok = sh_toknext(ctx->toks);
	*(char **)ft_vecpush(&av) = ft_strdup("test");
	ctx->proc->envv = makeenv(&ctx->vars, &ctx->proc->ownenv);
	ps_procexe(ctx->proc, "PATH", ((char **)av.buf)[0], ctx->proc->envv);
	makeargv(ctx, tok, &av, 1);
	*(char **)ft_vecpush(&av) = NULL;
	ctx->proc->argv = av.buf;
}
