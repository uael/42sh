/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

inline int	rl_editleft(void)
{
	if (g_eln->idx)
	{
		--g_eln->idx;
		rl_editprint(g_edit_prompt, g_eln);
	}
	return (YEP);
}

inline int	rl_editright(void)
{
	if (g_eln->idx != g_eln->str.len)
	{
		++g_eln->idx;
		rl_editprint(g_edit_prompt, g_eln);
	}
	return (YEP);
}

inline int	rl_edithome(void)
{
	if (g_eln->idx)
	{
		g_eln->idx = 0;
		rl_editprint(g_edit_prompt, g_eln);
	}
	return (YEP);
}

inline int	rl_editend(void)
{
	if (g_eln->idx != g_eln->str.len)
	{
		g_eln->idx = g_eln->str.len;
		rl_editprint(g_edit_prompt, g_eln);
	}
	return (YEP);
}
