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

static inline int		whileclause(t_while *s)
{
	g_sh->child = 1;
	sh_eval(-1, &s->cond, &s->ln) ? (g_sh->status = 1) : 0;
	while (!g_sh->status)
	{
		s->body.cur = 0;
		sh_eval(-1, &s->body, &s->ln) ? (g_sh->status = 1) : 0;
		s->cond.cur = 0;
		sh_eval(-1, &s->cond, &s->ln) ? (g_sh->status = 1) : 0;
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

static inline void		pushuntil(t_deq *dest, t_deq *src, char const *stop)
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

static inline t_while	*whileclausector(t_deq *toks, char **ln)
{
	t_while	*whilec;

	whilec = ft_malloc(sizeof(t_while));
	ft_bzero(whilec, sizeof(t_while));
	ft_deqctor(&whilec->cond, sizeof(t_tok));
	pushuntil(&whilec->cond, toks, (char []){TOK_DO, '\0'});
	ft_deqctor(&whilec->body, sizeof(t_tok));
	pushuntil(&whilec->body, toks, (char []){TOK_DONE, '\0'});
	sh_toknext(toks);
	whilec->ln = ft_strdup(*ln);
	return (whilec);
}

inline int				sh_evalwhileclause(t_proc *prc, t_deq *toks, char **ln)
{
	t_while	*whilec;

	whilec = whileclausector(toks, ln);
	if (g_sh->child)
	{
		whileclause(whilec);
		whileclausedtor(whilec);
		return (YEP);
	}
	ps_procfn(prc, (t_proccb *)whileclause, (t_dtor)whileclausedtor, whilec);
	return (YEP);
}
