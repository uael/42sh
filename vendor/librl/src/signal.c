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

#include "edit.h"
#include "visual.h"
#include "read.h"

inline int	rl_signalc(void)
{
	g_eln->idx = 0;
	g_eln->str.len = 0;
	*g_eln->str.buf = '\0';
	ft_write(STDIN_FILENO, "^C\n", 3);
	return (RL_CLR);
}

inline int	rl_signald(void)
{
	if (g_eln->str.len)
	{
		if (g_mode == RL_VISUAL)
			return (rl_visualdelete());
		return (YEP);
	}
	if (g_edit_cat)
		return (YEP);
	ft_sdsmpush(&g_eln->str, "exit", 4);
	rl_editprint();
	ft_write(STDIN_FILENO, "\n", 1);
	return (RL_EXIT);
}
