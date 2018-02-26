/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

#define ERR0 "syntax error: Unexpected closing token `%s'"

inline int	sh_lexcheck(t_src *s, t_deq *toks)
{
	size_t	i;
	t_tok	*t;
	t_tok	*p;

	i = 0;
	p = NULL;
	while (i < toks->len)
	{
		if (sh_syn(s, &p, t = ft_deqat(toks, i)))
			return (OUF);
		if (TOK_ISRGT(t->id))
			return (sh_synerr(*s->ln, *s->ln + t->pos, ERR0, sh_tokstr(t)));
		if (TOK_ISLFT(t->id))
		{
			if (!(i = sh_synbracket(s, toks, t, i)))
				return (OUF);
			p = ft_deqat(toks, i);
		}
		++i;
	}
	return (YEP);
}
