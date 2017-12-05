/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 16:21:12 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"

inline int	sh_bi_echo(t_sh *sh, int ac, char **av, char **env)
{
	int i;

	(void)sh;
	(void)env;
	if (ac < 2)
		return (ft_retf(OK, "\n"));
	i = 0;
	while (++i < ac)
	{
		ft_puts(1, av[i]);
		if (i < ac - 1)
			ft_putc(1, ' ');
	}
	return (ft_retf(OK, "\n"));
}
