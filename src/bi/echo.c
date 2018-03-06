/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/bi.h"

inline int	sh_biecho(int ac, char **argv, char **env)
{
	int i;
	int n_flag;

	(void)env;
	if (!argv[(i = 0) + 1])
		return (ft_putc(STDOUT_FILENO, '\n') < 0 ? EXIT_FAILURE : EXIT_SUCCESS);
	else if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0')
		++i;
	n_flag = i;
	while (++i < ac)
		if (ft_puts(STDOUT_FILENO, argv[i]) < 0 ||
			(i < ac - 1 ? ft_putc(STDOUT_FILENO, ' ') : 0) < 0)
			return (EXIT_FAILURE);
	if ((n_flag ? 0 : ft_putc(STDOUT_FILENO, '\n')) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
