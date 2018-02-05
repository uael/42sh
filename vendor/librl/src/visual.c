/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:13:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "read.h"

static char		g_clipboard[MAX_INPUT + 1] = { 0 };

inline int		rl_visualtoggle(void)
{
	if (g_mode == RL_VISUAL)
	{
		g_mode = RL_INSERT;
		rl_editprint();
	}
	else
	{
		g_mode = RL_VISUAL;
		g_eln->vidx = g_eln->idx;
	}
	return (YEP);
}

inline int		rl_visualyank(void)
{
	size_t i;

	if (g_mode == RL_INSERT && g_eln->idx < g_eln->len)
	{
		g_clipboard[0] = g_eln->buf[g_eln->idx];
		g_clipboard[1] = '\0';
	}
	else if (g_mode == RL_VISUAL && g_eln->vidx > g_eln->idx)
	{
		i = g_eln->vidx == g_eln->len ? g_eln->vidx - 1 : g_eln->vidx;
		ft_strncpy(g_clipboard, g_eln->buf + g_eln->idx, i - g_eln->idx + 1);
		g_eln->idx = g_eln->vidx;
		rl_visualtoggle();
	}
	else if (g_mode == RL_VISUAL && g_eln->vidx < g_eln->idx)
	{
		i = g_eln->idx == g_eln->len ? g_eln->idx - 1 : g_eln->idx;
		ft_strncpy(g_clipboard, g_eln->buf + g_eln->vidx, i - g_eln->vidx + 1);
		g_eln->vidx = g_eln->idx;
		rl_visualtoggle();
	}
	return (YEP);
}

inline int		rl_visualdelete(void)
{
	size_t i;

	if (g_eln->vidx > g_eln->idx)
	{
		i = g_eln->vidx == g_eln->len ? g_eln->vidx - 1 : g_eln->vidx;
		ft_strncpy(g_clipboard, g_eln->buf + g_eln->idx, i - g_eln->idx + 1);
		i = i - g_eln->idx + 1;
		ft_memmove(g_eln->buf + g_eln->idx, g_eln->buf + g_eln->idx + i,
			g_eln->len - i);
		g_eln->buf[g_eln->len -= i] = '\0';
		g_eln->vidx = g_eln->idx;
		rl_visualtoggle();
	}
	else if (g_eln->vidx < g_eln->idx)
	{
		i = g_eln->idx == g_eln->len ? g_eln->idx - 1 : g_eln->idx;
		ft_strncpy(g_clipboard, g_eln->buf + g_eln->vidx, i - g_eln->vidx + 1);
		i = i - g_eln->vidx + 1;
		ft_memmove(g_eln->buf + g_eln->vidx, g_eln->buf + g_eln->vidx + i,
			g_eln->len - i);
		g_eln->buf[g_eln->len -= i] = '\0';
		g_eln->idx = g_eln->vidx;
		rl_visualtoggle();
	}
	return (YEP);
}

inline int		rl_visualpaste(void)
{
	size_t n;

	if (*g_clipboard)
	{
		n = ft_strlen(g_clipboard);
		if (g_eln->len + 1 < MAX_INPUT)
		{
			if ((MAX_INPUT - g_eln->len + 1) < n)
				n = MAX_INPUT - g_eln->len + 1;
			if (g_eln->idx != g_eln->len)
				ft_memmove(g_eln->buf + g_eln->idx + n, g_eln->buf + g_eln->idx,
					g_eln->len - g_eln->idx);
			ft_memcpy(g_eln->buf + g_eln->idx, g_clipboard, n);
			g_eln->buf[g_eln->len += n] = '\0';
			rl_editprint();
		}
	}
	return (YEP);
}
