/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../read.h"

inline int	rl_editreturn(void)
{
	if (g_mode == RL_SEARCH)
		return (rl_searchinsert('\n'));
	if (g_eln->str.len)
		ft_sdscpush(&g_eln->str, '\n');
	ft_write(STDOUT_FILENO, "\n", 1);
	if (!g_eln->str.len)
	{
		rl_editprint(g_edit_prompt, g_eln);
		return (YEP);
	}
	return (NOP);
}
