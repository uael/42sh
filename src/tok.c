/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/tok.h"

inline t_tok	*sh_tokpeek(t_deq *toks)
{
	if (ft_deqlen(toks))
		return (ft_deqbeg(toks));
	return (NULL);
}

inline t_tok	*sh_toknext(t_deq *toks)
{
	ft_deqsht(toks, NULL);
	return (sh_tokpeek(toks));
}

inline void		sh_tokdtor(t_tok *tok)
{
	ft_sdsdtor((t_sds *)tok);
	ft_memset(tok, 0, sizeof(t_tok));
}

inline t_tok2	*sh_tokpos(t_tok2 *tok, char const *it, char const *ln)
{
	char *pos;

	pos = (char *)it;
	while (pos > ln && !ISEOL(pos - 1))
		--pos;
	tok->pos = (uint16_t)(it - pos);
	return (tok);
}
