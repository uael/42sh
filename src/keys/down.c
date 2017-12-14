/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys/down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:06:07 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/keys.h"

inline int	sh_keys_down(t_sh *self, t_tc *tc)
{
	if (self->cursor < ft_vstr_size(&self->history))
		++self->cursor;
	tc_clrln(tc);
	if (self->cursor < ft_vstr_size(&self->history))
		tc_putnl(tc, *ft_vstr_at(&self->history, self->cursor));
	return (YEP);
}
