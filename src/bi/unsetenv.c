/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:31:25 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"
#include "msh/env.h"

inline t_st	msh_bi_unsetenv(t_msh *self, t_vstr *av)
{
	t_st	st;
	size_t	i;
	t_st 	fst;

	if (av->len < 2)
		return (ft_ret(NOK, "%s: %e", "unset", E2BIG));
	i = 0;
	fst = OK;
	while (++i < av->len)
		if (ft_strchr(av->buf[i], '='))
			return (ft_ret(NOK, "%s: %s", "unset", "Syntax error"));
		else if (ISE(st = msh_unsetenv(self, av->buf[i])))
			return (st);
		else if (ST_NOK(st))
			ft_ret((fst = NOK), "%s: %s '%s'",
				"unset", "Environ not fount", av->buf[i]);
	return (fst);
}
