/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

#define ERR0 "syntax error: Expected `%s' after `%s' got `%s'"

static int	andorerr(t_src *s, t_deq *toks, size_t const *idx, size_t andor)
{
	t_tok	*tok;
	t_tok	*tok2;

	tok = ft_deqat(toks, andor);
	tok2 = *idx >= toks->len ? NULL : ft_deqat(toks, *idx);
	return (sh_evalerr(*s->ln, tok2, ERR0,
		"<pipeline>", sh_tokstr(tok), sh_tokstr(tok2)));
}

inline int	sh_synandor(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;
	size_t	andor;

	if ((st = sh_synpipeline(s, toks, idx)))
		return (st);
	while (*idx < toks->len)
	{
		tok = ft_deqat(toks, *idx);
		if (tok->id != TOK_LOR && tok->id != TOK_LAND)
			return (YEP);
		andor = *idx;
		while (++*idx < toks->len)
			if (((t_tok *)ft_deqat(toks, *idx))->id != '\n')
				break ;
		if ((st = sh_synpipeline(s, toks, idx)) == NOP)
			return (andorerr(s, toks, idx, andor));
		else if (st)
			return (st);
	}
	return (YEP);
}
