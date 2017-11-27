/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:31:34 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"

inline t_ret	msh_bi_env(t_msh *self, t_vstr *av)
{
	size_t i;

	(void)self;
	if (av->len != 1)
		return (RET_NOK);
	i = 0;
	while (i < self->env.len)
		ft_putl(1, self->env.buf[i++]);
	return (RET_NOK);
}
