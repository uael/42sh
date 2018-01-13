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

static t_sds	g_clipboard_stack = { NULL, 0, 0 };
static t_sds	*g_clipboard = &g_clipboard_stack;

inline void		rl_visualdtor(void)
{
	ft_sdsdtor(g_clipboard);
}

inline int		rl_visualtoggle(char const *prompt)
{
	if (g_mode == RL_VISUAL)
	{
		g_mode = RL_INSERT;
		rl_editprint(prompt);
	}
	else
	{
		g_mode = RL_VISUAL;
		g_editln->vidx = g_editln->idx;
	}
	return (YEP);
}

inline int		rl_visualyank(char const *prompt)
{
	uint16_t	i;

	if (g_mode == RL_INSERT && g_editln->idx < g_editln->str.len)
		ft_sdscpush(g_clipboard, *ft_sdsat(&g_editln->str, g_editln->idx));
	else if (g_mode == RL_VISUAL && g_editln->vidx > g_editln->idx)
	{
		i = (uint16_t) (g_editln->vidx == g_editln->str.len
			? g_editln->vidx - 1 : g_editln->vidx);
		g_clipboard->len = 0;
		ft_sdsmpush(g_clipboard, ft_sdsat(&g_editln->str, g_editln->idx),
			i - g_editln->idx);
		g_editln->idx = g_editln->vidx;
		rl_editprint(prompt);
	}
	else if (g_mode == RL_VISUAL && g_editln->vidx < g_editln->idx)
	{
		i = (uint16_t) (g_editln->idx == g_editln->str.len
			? g_editln->idx - 1 : g_editln->idx);
		g_clipboard->len = 0;
		ft_sdsmpush(g_clipboard, ft_sdsat(&g_editln->str, g_editln->vidx),
			i - g_editln->vidx);
		g_editln->vidx = g_editln->idx;
		rl_editprint(prompt);
	}
	return (YEP);
}

inline int		rl_visualdelete(char const *prompt)
{
	uint16_t	i;

	if (g_editln->vidx > g_editln->idx)
	{
		i = (uint16_t) (g_editln->vidx == g_editln->str.len
			? g_editln->vidx - 1 : g_editln->vidx);
		g_clipboard->len = 0;
		ft_sdsmpush(g_clipboard, ft_sdsat(&g_editln->str, g_editln->idx),
			i - g_editln->idx);
		ft_sdsnrem(&g_editln->str, g_editln->idx, i - g_editln->idx, NULL);
		g_editln->vidx = g_editln->idx;
		rl_editprint(prompt);
	}
	else if (g_editln->vidx < g_editln->idx)
	{
		i = (uint16_t) (g_editln->idx == g_editln->str.len
			? g_editln->idx - 1 : g_editln->idx);
		g_clipboard->len = 0;
		ft_sdsmpush(g_clipboard, ft_sdsat(&g_editln->str, g_editln->vidx),
			i - g_editln->vidx);
		ft_sdsnrem(&g_editln->str, g_editln->vidx, i - g_editln->vidx, NULL);
		g_editln->idx = g_editln->vidx;
		rl_editprint(prompt);
	}
	return (YEP);
}

inline int		rl_visualpaste(char const *prompt)
{
	if (g_clipboard->len)
	{
		ft_sdsmput(&g_editln->str, g_editln->idx, g_clipboard->buf,
			g_clipboard->len);
		g_editln->idx += g_clipboard->len;
		rl_editprint(prompt);
	}
	return (YEP);
}
