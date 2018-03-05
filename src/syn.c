/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

#define ERR0 "syntax error: Unexpected token `%s'"

static int	synerr(t_src *s, t_deq *toks, size_t const *idx)
{
	t_tok	*tok;

	tok = *idx >= toks->len ? NULL : ft_deqat(toks, *idx);
	return (sh_evalerr(*s->ln, tok, ERR0, sh_tokstr(tok)));
}

inline void	sh_synlinebreak(t_deq *toks, size_t const *idx)
{
	while (*idx < toks->len)
	{
		if (((t_tok *)ft_deqat(toks, *idx))->id != '\n')
			break ;
		ft_deqrem(toks, *idx, NULL);
	}
}

inline int	sh_syncheck(t_src *s, t_deq *toks)
{
	size_t	idx;
	int		st;
	t_tok	*tok;

	idx = 0;
	if ((st = sh_synlist(s, toks, &idx)))
		return (st == NOP ? synerr(s, toks, &idx) : st);
	if (idx >= toks->len)
		return (YEP);
	tok = ft_deqat(toks, idx);
	if (tok->id == '\0')
		return (YEP);
	if (tok->id == '&' || tok->id == ';')
		tok = ft_deqat(toks, ++idx);
	if (!sh_tokis(tok, TOKS_END))
		return (synerr(s, toks, &idx));
	while (sh_tokis(tok, TOKS_END))
	{
		if (++idx == toks->len)
			return (YEP);
		tok = ft_deqat(toks, idx);
	}
	return (synerr(s, toks, &idx));
}
