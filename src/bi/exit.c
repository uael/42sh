/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:30:36 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"

#define M_NBREQ "Numeric argument required"

inline t_st	msh_bi_exit(t_msh *self, t_vstr *av)
{
	size_t	i;
	size_t	j;
	char	*a;

	if (av->len > 2)
		return (ft_ret(NOK, "%s: %e\n", "exit", E2BIG));
	if (av->len < 2)
		SH_EXIT(self->st, self, NULL);
	a = av->buf[1];
	if (!(i = ft_strlen(a)) || i > 19)
		SH_EXIT(NOK, "%s: %s, got '%s' instead\n", "exit", M_NBREQ, a);
	j = 0;
	while (j < i)
		if (!ft_isdigit(a[j]) && !ft_isspace(a[j]))
			SH_EXIT(NOK, "%s: %s, got '%s' instead\n", "exit", M_NBREQ, a);
		else
			j++;
	return (SH_EXIT((int)ft_atoi(a), self, NULL));
}
