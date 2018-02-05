/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/ins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"
#include "../read.h"
#include "../visual.h"

inline int	rl_editinsert(char c)
{
	if (c == '\n' || c == '\r')
		return (rl_editreturn());
	if (g_eln->len + 1 < MAX_INPUT)
	{
		if (g_eln->idx != g_eln->len)
			ft_memmove(g_eln->buf + g_eln->idx + 1, g_eln->buf + g_eln->idx,
				g_eln->len - g_eln->idx);
		g_eln->buf[g_eln->idx++] = c;
		g_eln->buf[++g_eln->len] = '\0';
		rl_editprint();
	}
	return (YEP);
}

inline int	rl_editdelete(void)
{
	if (g_eln->idx < g_eln->len)
	{
		if (g_mode == RL_VISUAL && g_eln->idx != g_eln->vidx)
			return (rl_visualdelete());
		ft_memmove(g_eln->buf + g_eln->idx, g_eln->buf + g_eln->idx + 1,
			g_eln->len - g_eln->idx);
		rl_editprint();
	}
	return (YEP);
}

inline int	rl_editbackspace(void)
{
	if (g_eln->idx && g_eln->len)
	{
		if (g_mode == RL_VISUAL && g_eln->idx != g_eln->vidx)
			return (rl_visualdelete());
		--g_eln->idx;
		ft_memmove(g_eln->buf + g_eln->idx, g_eln->buf + g_eln->idx + 1,
			g_eln->len - g_eln->idx);
		rl_editprint();
	}
	return (YEP);
}

inline int	rl_editclear(void)
{
	ft_puts(STDIN_FILENO, TC_ED_CUP);
	g_eln->row = 0;
	g_eln->rows.len = 0;
	rl_editprint();
	return (YEP);
}
