/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/ifclause.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

inline int	sh_synifclause(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	if ((st = sh_syncompoundlist(s, toks, idx,
		(char const[]){TOK_THEN, '\0'})))
		return (st);
	if ((st = sh_syncompoundlist(s, toks, idx,
		(char const[]){TOK_ELIF, TOK_ELSE, TOK_FI, '\0'})))
		return (st);
	tok = ft_deqat(toks, *idx);
	if (tok->id == TOK_ELIF)
		return (sh_synifclause(s, toks, idx));
	if (tok->id == TOK_FI)
	{
		++*idx;
		return (YEP);
	}
	if ((st = sh_syncompoundlist(s, toks, idx,
		(char const[]){TOK_FI, '\0'})))
		return (st);
	++*idx;
	return (YEP);
}
