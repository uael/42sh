/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/whileclause.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static int		whileclause(t_while *s)
{
	g_sh->child = 1;
	sh_eval(&s->cond, s->ln);
	while (!g_sh->status)
	{
		s->body.cur = 0;
		sh_eval(&s->body, s->ln);
		s->cond.cur = 0;
		sh_eval(&s->cond, s->ln);
	}
	return (g_sh->status);
}

static void		whileclausedtor(t_while *s)
{
	ft_deqdtor(&s->cond, NULL);
	ft_deqdtor(&s->body, NULL);
	free(s->ln);
	free(s);
}

static void		pushuntila(t_deq *dest, t_deq *src, char const *stop)
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

static t_while	*whileclausector(t_deq *toks, char const *ln)
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

inline void		sh_evalwhile(t_ctx *ctx, t_tok *tok)
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
	ctx->proc->child = (t_bool)(g_sh->child ? 0 : 1);
}
