/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/untilclause.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static int		untilclause(t_loop *s)
{
	g_sh->child = 1;
	sh_eval(&s->cond, s->ln);
	while (g_sh->status)
	{
		s->body.cur = 0;
		sh_eval(&s->body, s->ln);
		s->cond.cur = 0;
		sh_eval(&s->cond, s->ln);
	}
	return (g_sh->status = 0);
}

static void		untilclausedtor(t_loop *s)
{
	ft_deqdtor(&s->cond, NULL);
	ft_deqdtor(&s->body, NULL);
	free(s->ln);
	free(s);
}

static t_loop	*untilclausector(t_deq *toks, char const *ln)
{
	t_loop	*untilc;

	untilc = ft_malloc(sizeof(t_loop));
	ft_bzero(untilc, sizeof(t_loop));
	ft_deqctor(&untilc->cond, sizeof(t_tok));
	sh_pushuntil(&untilc->cond, toks, (char[]){TOK_DO, '\0'},
		(char[]){TOK_DO, TOK_DONE});
	ft_deqctor(&untilc->body, sizeof(t_tok));
	sh_pushuntil(&untilc->body, toks, (char[]){TOK_DONE, '\0'},
		(char[]){TOK_DO, TOK_DONE});
	sh_toknext(toks);
	untilc->ln = ft_strdup(ln);
	return (untilc);
}

inline void		sh_evaluntil(t_ctx *ctx, t_tok *tok)
{
	t_loop	*untilc;

	(void)tok;
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	untilc = untilclausector(ctx->toks, ctx->ln);
	ps_procfn(ctx->proc, (t_proccb *)untilclause, (t_dtor)untilclausedtor,
		untilc);
	ctx->proc->child = (t_bool)(g_sh->child ? 0 : 1);
}
