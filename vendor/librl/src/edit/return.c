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

#include "../edit.h"

inline int	rl_editreturn(void)
{
	if (g_eln->idx != g_eln->len)
	{
		g_eln->idx = (uint16_t)g_eln->len;
		rl_editprint();
	}
	g_eln->buf[g_eln->len++] = '\n';
	ft_write(STDIN_FILENO, "\n", 1);
	return (NOP);
}
