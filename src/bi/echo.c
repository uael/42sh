/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 18:41:10 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"

inline t_st	sh_bi_echo(t_sh *self, t_vstr *av)
{
	size_t i;

	(void)self;
	if (av->len < 2)
		return (ft_retf(OK, "\n"));
	i = 0;
	while (++i < av->len)
	{
		ft_puts(1, av->buf[i]);
		if (i < av->len - 1)
			ft_putc(1, ' ');
	}
	return (ft_retf(OK, "\n"));
}
