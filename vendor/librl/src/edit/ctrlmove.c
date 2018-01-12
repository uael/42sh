/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/ctrlmove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

inline int	rl_editctrlleft(char const *prompt)
{
	size_t	idx;

	idx = g_editln->idx;
	while (g_editln->idx > 0 &&
		ft_isspace(g_editln->str.buf[g_editln->idx - 1]))
		--g_editln->idx;
	while (g_editln->idx > 0 &&
		!ft_isspace(g_editln->str.buf[g_editln->idx - 1]))
		--g_editln->idx;
	if (g_editln->idx != idx)
		rl_editprint(prompt);
	return (YEP);
}

inline int	rl_editctrlright(char const *prompt)
{
	size_t	idx;

	idx = g_editln->idx;
	while (g_editln->idx < g_editln->str.len &&
		!ft_isspace(g_editln->str.buf[g_editln->idx + 1]))
		++g_editln->idx;
	while (g_editln->idx < g_editln->str.len &&
		ft_isspace(g_editln->str.buf[g_editln->idx + 1]))
		++g_editln->idx;
	if (g_editln->idx < g_editln->str.len)
		++g_editln->idx;
	if (g_editln->idx != idx)
		rl_editprint(prompt);
	return (YEP);
}

inline int	rl_editctrlup(char const *prompt)
{
	size_t		plen;
	uint16_t	c;
	uint16_t	cur;

	if (g_editln->row <= 1)
		return (YEP);
	plen = ft_strlen(prompt);
	if ((g_editln->row - 1) == 1 && (g_screen->cursor < plen))
		g_editln->idx = 0;
	else
	{
		c = *(uint16_t *)ft_vecat(&g_editln->cols, (size_t)(g_editln->row - 2));
		while (g_editln->str.buf[--g_editln->idx] != '\n')
			;
		while (g_editln->idx &&
			g_editln->str.buf[g_editln->idx - 1] != '\n')
			--g_editln->idx;
		cur = g_screen->cursor;
		g_screen->cursor = (uint16_t)((g_editln->row - 1) == 1 ? plen : 0);
		while (g_screen->cursor < cur && g_screen->cursor < c)
			g_screen->cursor += (g_editln->str.buf[g_editln->idx++] == '\t' ?
				(8 - (g_screen->cursor % 8)) : 1);
	}
	rl_editprint(prompt);
	return (YEP);
}

inline int	rl_editctrldown(char const *prompt)
{
	uint16_t	c;
	uint16_t	cur;

	if (g_editln->row == g_editln->rows)
		return (YEP);
	c = *(uint16_t *)ft_vecat(&g_editln->cols, (size_t)(g_editln->row));
	while (g_editln->str.buf[g_editln->idx] != '\n')
		++g_editln->idx;
	++g_editln->idx;
	cur = g_screen->cursor;
	g_screen->cursor = 0;
	while (g_screen->cursor < cur && g_screen->cursor < c)
		g_screen->cursor += (g_editln->str.buf[g_editln->idx++] == '\t' ?
			(8 - (g_screen->cursor % 8)) : 1);
	rl_editprint(prompt);
	return (YEP);
}
