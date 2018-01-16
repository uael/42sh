/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/ln.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

inline void		rl_editlnupdate(t_editln *ln)
{
	char *beg;
	char *eol;

	ln->rows.len = 0;
	beg = ln->str.buf;
	while ((eol = ft_strchr(beg, '\n')))
	{
		*(char **)ft_vecpush(&ln->rows) = beg;
		beg = eol + 1;
	}
	*(char **)ft_vecpush(&ln->rows) = beg;
}
