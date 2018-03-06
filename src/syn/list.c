/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

inline int	sh_synlist(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	if ((st = sh_synandor(s, toks, idx)))
		return (st);
	while (*idx < toks->len)
	{
		tok = ft_deqat(toks, *idx);
		if (tok->id != '&' && tok->id != ';')
			return (YEP);
		++*idx;
		if ((st = sh_synandor(s, toks, idx)))
			return (st == NOP ? YEP : st);
	}
	return (YEP);
}
