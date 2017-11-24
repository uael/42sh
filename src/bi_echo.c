/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 18:41:10 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline t_ret	msh_bi_echo(t_msh *self, t_vstr *av)
{
	size_t i;

	(void)self;
	if (av->len < 2)
		return (RET_NOK);
	i = 0;
	while (++i < av->len)
	{
		ft_puts(1, av->buf[i]);
		if (i < av->len - 1)
			ft_putc(1, ' ');
	}
	ft_putc(1, '\n');
	return (RET_OK);
}
