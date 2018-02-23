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

static inline int			whileclause(t_whileclause *s)
{
	t_scope	*sh;
	int		st;

	sh = g_sh;
	ft_memcpy(g_sh, sh, sizeof(t_scope));
	g_sh->tty = 0;
	sh_eval(-1, &s->cond, &s->ln) ? (g_sh->status = 1) : 0;
	while (!g_sh->status)
	{
		s->body.cur = 0;
		sh_eval(-1, &s->body, &s->ln) ? (g_sh->status = 1) : 0;
		s->cond.cur = 0;
		sh_eval(-1, &s->cond, &s->ln) ? (g_sh->status = 1) : 0;
	}
	st = g_sh->status;
	return (sh_exit(st, NULL));
}

static inline void			whileclausedtor(t_whileclause *s)
{
	ft_deqdtor(&s->cond, NULL);
	ft_deqdtor(&s->body, NULL);
	free(s->ln);
	free(s);
}

static inline t_whileclause	*whileclausector(t_deq *toks, char **ln)
{
	t_whileclause	*whilec;
	t_tok			*tok;

	whilec = ft_malloc(sizeof(t_whileclause));
	ft_bzero(whilec, sizeof(t_whileclause));
	ft_deqctor(&whilec->cond, sizeof(t_tok));
	ft_deqctor(&whilec->body, sizeof(t_tok));
	while ((tok = sh_toknext(toks))->id != TOK_DO)
		*(t_tok *)ft_deqpush(&whilec->cond) = *tok;
	(*(t_tok *)ft_deqpush(&whilec->cond)).id = TOK_END;
	while ((tok = sh_toknext(toks))->id != TOK_DONE)
		*(t_tok *)ft_deqpush(&whilec->body) = *tok;
	(*(t_tok *)ft_deqpush(&whilec->body)).id = TOK_END;
	sh_toknext(toks);
	whilec->ln = ft_strdup(*ln);
	return (whilec);
}

inline int					sh_evalwhileclause(t_proc *prc, t_deq *toks,
	char **ln)
{
	ps_procfn(prc, (t_proccb *)whileclause, (t_dtor)whileclausedtor,
		whileclausector(toks, ln));
	return (YEP);
}
