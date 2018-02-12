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
	if (!rl_histbi())
	{
		ft_write(STDIN_FILENO, "\n", 1);
		ft_putf(STDIN_FILENO, "%s\n", g_eln->str.buf);
	}
	else if (g_eln->idx != g_eln->str.len)
	{
		g_eln->idx = (uint16_t)g_eln->str.len;
		rl_editprint(g_edit_prompt, g_eln);
		ft_write(STDIN_FILENO, "\n", 1);
	}
	else
		ft_write(STDIN_FILENO, "\n", 1);
	ft_sdscpush(&g_eln->str, '\n');
	return (NOP);
}
