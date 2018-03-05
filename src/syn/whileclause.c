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

inline int	sh_synwhileclause(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;

	if ((st = sh_syncompoundlist(s, toks, idx,
		(char const[]){TOK_DO, '\0'})))
		return (st);
	if ((st = sh_syncompoundlist(s, toks, idx,
		(char const[]){TOK_DONE, '\0'})))
		return (st);
	++*idx;
	return (YEP);
}
