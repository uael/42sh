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

inline t_ret	msh_bi_exit(t_msh *self, t_vstr *av)
{
	size_t	i;
	size_t	j;
	char	*a;

	if (av->len > 2)
		return (CMD_NOK("exit: Too many arguments"));
	if (av->len < 2)
		MSH_EXIT(self->st, self);
	a = av->buf[1];
	if (!(i = ft_strlen(a)) || i > 19)
	{
		ft_putl(2, "exit: Numeric argument required");
		MSH_EXIT(EXIT_FAILURE, self);
	}
	j = 0;
	while (j < i)
		if (!ft_isdigit(a[j]) && !ft_isspace(a[j]))
		{
			ft_putl(2, "exit: Numeric argument required");
			MSH_EXIT(EXIT_FAILURE, self);
		}
		else
			j++;
	MSH_EXIT((int)ft_atoi(a), self);
}
