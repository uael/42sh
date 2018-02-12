/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

inline int	rl_editctrlleft(void)
{
	size_t idx;

	idx = g_eln->idx;
	while (g_eln->idx > 0 &&
		ft_isspace(g_eln->str.buf[g_eln->idx - 1]))
		--g_eln->idx;
	while (g_eln->idx > 0 &&
		!ft_isspace(g_eln->str.buf[g_eln->idx - 1]))
		--g_eln->idx;
	if (g_eln->idx != idx)
		rl_editprint();
	return (YEP);
}

inline int	rl_editctrlright(void)
{
	size_t idx;

	idx = g_eln->idx;
	while (g_eln->idx < g_eln->str.len &&
		!ft_isspace(g_eln->str.buf[g_eln->idx + 1]))
		++g_eln->idx;
	while (g_eln->idx < g_eln->str.len &&
		ft_isspace(g_eln->str.buf[g_eln->idx + 1]))
		++g_eln->idx;
	if (g_eln->idx < g_eln->str.len)
		++g_eln->idx;
	if (g_eln->idx != idx)
		rl_editprint();
	return (YEP);
}

inline int	rl_editctrlup(void)
{
	char *row;
	char *pos;
	char *pre;

	if (g_eln->row <= 1)
		return (YEP);
	row = *(char **)ft_vecat(&g_eln->rows, (size_t)(g_eln->row - 2));
	pre = *(char **)ft_vecat(&g_eln->rows, (size_t)(g_eln->row - 1));
	pos = ft_sdsat(&g_eln->str, g_eln->idx);
	g_eln->idx = (uint16_t)(row - ft_sdsbeg(&g_eln->str));
	while (pos > pre && g_eln->str.buf[g_eln->idx] != '\n' &&
		g_eln->idx < g_eln->str.len)
	{
		++g_eln->idx;
		--pos;
	}
	rl_editprint();
	return (YEP);
}

inline int	rl_editctrldown(void)
{
	char *row;
	char *pos;
	char *pre;

	if (g_eln->row == g_eln->rows.len)
		return (YEP);
	row = *(char **)ft_vecat(&g_eln->rows, (size_t)(g_eln->row));
	pre = *(char **)ft_vecat(&g_eln->rows, (size_t)(g_eln->row - 1));
	pos = ft_sdsat(&g_eln->str, g_eln->idx);
	g_eln->idx = (uint16_t)(row - ft_sdsbeg(&g_eln->str));
	while (pos > pre && g_eln->str.buf[g_eln->idx] != '\n' &&
		g_eln->idx < g_eln->str.len)
	{
		++g_eln->idx;
		--pos;
	}
	rl_editprint();
	return (YEP);
}

inline int	rl_edittab(void)
{
	if (g_eln->idx != g_eln->str.len)
	{
		g_eln->idx = (uint16_t)g_eln->str.len;
		rl_editprint();
	}
	else if (!rl_histbi())
		return (YEP);
	else if (g_rlcomp)
	{
		g_rlcomp(&g_eln->str);
		g_eln->idx = (uint16_t)g_eln->str.len;
		rl_editprint();
	}
	return (YEP);
}
