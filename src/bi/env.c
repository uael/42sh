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

inline t_st	msh_bi_env(t_msh *self, t_vstr *av)
{
	size_t i;

	(void)self;
	if (av->len != 1)
		return (ft_ret(NOK, "%s: %e", "env", E2BIG));
	i = 0;
	while (i < self->env.len)
		if (self->env.buf[i++])
			ft_putl(1, self->env.buf[i - 1]);
	return (OK);
}
