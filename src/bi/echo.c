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

inline int	sh_bi_echo(t_sh *sh, int ac, char **av, t_job *out)
{
	int i;

	(void)sh;
	(void)out;
	if (ac < 2)
		return (sh_bi_retf(sh, YEP, "\n"));
	i = 0;
	while (++i < ac)
	{
		ft_omstream_puts(&sh->bi_out, av[i]);
		if (i < ac - 1)
			ft_omstream_putc(&sh->bi_out, ' ');
	}
	ft_omstream_putc(&sh->bi_out, '\n');
	return (YEP);
}
