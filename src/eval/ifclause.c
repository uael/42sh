/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/ifclause.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static int	ifclause(t_if *s)
{
	sh_eval(&s->cond, s->ln);
	if (!g_sh->status)
		sh_eval(&s->body, s->ln);
	else if (s->elsekind == ELSE_ELIF)
		return (ifclause(s->elsepart.elif));
	else if (s->elsekind == ELSE_ELSE)
		sh_eval(&s->elsepart.body, s->ln);
	return (g_sh->status);
}

static void	ifclausedtor(t_if *s)
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

static void	pushuntil(t_deq *dest, t_deq *src, char const *stop)
{
	sh_pushuntil(dest, src, stop, (char[]){TOK_IF, TOK_FI});
}

static t_if	*ifclausector(t_deq *toks, char const *ln)
{
	t_if	*ifc;
	t_tok	*tok;

	ifc = ft_malloc(sizeof(t_if));
	ft_bzero(ifc, sizeof(t_if));
	ft_deqctor(&ifc->cond, sizeof(t_tok));
	pushuntil(&ifc->cond, toks, (char[]){TOK_THEN, '\0'});
	ft_deqctor(&ifc->body, sizeof(t_tok));
	pushuntil(&ifc->body, toks, (char[]){TOK_ELSE, TOK_ELIF, TOK_FI, '\0'});
	if ((tok = sh_tokpeek(toks))->id == TOK_ELSE)
	{
		ifc->elsekind = ELSE_ELSE;
		ft_deqctor(&ifc->elsepart.body, sizeof(t_tok));
		pushuntil(&ifc->elsepart.body, toks, (char[]){TOK_FI, '\0'});
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

inline void	sh_evalif(t_ctx *ctx, t_tok *tok)
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
