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

static inline int			ifclause(t_if *s)
{
	g_sh->tty = 0;
	sh_eval(-1, &s->cond, &s->ln) ? (g_sh->status = 1) : 0;
	if (!g_sh->status)
		sh_eval(-1, &s->body, &s->ln) ? (g_sh->status = 1) : 0;
	else if (s->elsekind == ELSE_ELIF)
		return (ifclause(s->elsepart.elif));
	else if (s->elsekind == ELSE_ELSE)
		sh_eval(-1, &s->elsepart.body, &s->ln) ? (g_sh->status = 1) : 0;
	return (g_sh->status);
}

static inline void			ifclausedtor(t_if *s)
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

static inline t_tok			*ifclauseinit(t_if *ifc, t_deq *toks)
{
	t_tok *tok;

	ft_bzero(ifc, sizeof(t_if));
	ft_deqctor(&ifc->cond, sizeof(t_tok));
	ft_deqctor(&ifc->body, sizeof(t_tok));
	while ((tok = sh_toknext(toks))->id != TOK_THEN)
		*(t_tok *)ft_deqpush(&ifc->cond) = *tok;
	(*(t_tok *)ft_deqpush(&ifc->cond)).id = TOK_END;
	while ((tok = sh_toknext(toks))->id != TOK_ELSE && tok->id != TOK_ELIF &&
		tok->id != TOK_FI)
		*(t_tok *)ft_deqpush(&ifc->body) = *tok;
	(*(t_tok *)ft_deqpush(&ifc->body)).id = TOK_END;
	return (tok);
}

static inline t_if	*ifclausector(int fd, t_deq *toks, char **ln)
{
	t_if	*ifc;
	t_tok		*tok;

	ifc = ft_malloc(sizeof(t_if));
	tok = ifclauseinit(ifc, toks);
	if (tok->id == TOK_ELSE)
	{
		ifc->elsekind = ELSE_ELSE;
		ft_deqctor(&ifc->elsepart.body, sizeof(t_tok));
		while ((tok = sh_toknext(toks))->id != TOK_FI)
			*(t_tok *)ft_deqpush(&ifc->elsepart.body) = *tok;
		(*(t_tok *)ft_deqpush(&ifc->elsepart.body)).id = TOK_END;
		sh_toknext(toks);
	}
	else if (tok->id == TOK_ELIF)
	{
		ifc->elsekind = ELSE_ELIF;
		ifc->elsepart.elif = ifclausector(fd, toks, ln);
	}
	else
		sh_toknext(toks);
	ifc->ln = ft_strdup(*ln);
	return (ifc);
}

inline int					sh_evalifclause(t_proc *prc, int fd, t_deq *toks,
	char **ln)
{
	ps_procfn(prc, (t_proccb *)ifclause, (t_dtor)ifclausedtor,
		ifclausector(fd, toks, ln));
	return (YEP);
}
