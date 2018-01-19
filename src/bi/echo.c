/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/bi.h"

static int	exhdl(int rcode, void *arg)
{
	(void)arg;
	errno = 0;
	return (rcode);
}

inline int	sh_biecho(int ac, char **argv, char **env)
{
	int			i;
	int			n_flag;
	t_ex_hdl	dfl;

	(void)env;
	ft_exbind(EXALL, ft_exhdl(exhdl, NULL), &dfl);
	n_flag = 0;
	if (!argv[1])
	{
		ft_write(1, "\n", 1);
		ft_exbind(EXALL, dfl, NULL);
		return (EXIT_SUCCESS);
	}
	else if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0')
		n_flag = 1;
	i = 0;
	if (n_flag)
		++i;
	while (++i < ac)
	{
		ft_puts(1, argv[i]);
		if (!argv[i + 1] && !n_flag)
			ft_putc(1, '\n');
	}
	ft_exbind(EXALL, dfl, NULL);
	return (EXIT_SUCCESS);
}