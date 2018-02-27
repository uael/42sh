/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/bi/history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/bi.h"
#include "ush/env.h"
#include "ush/shell.h"

inline int		sh_bihistory(int ac, char **av, char **env)
{
	char 	*home;
	char	buf[PATH_MAX];

	if(!g_sh->tty)
		return (EXIT_FAILURE);
	(void)env;
	if (ac == 2 && !ft_strcmp(av[1], "-c"))
		rl_histdtor();
	else if (ac == 3 && !ft_strcmp(av[1], "-d"))
		rl_histdel((uint8_t)ft_atoi(av[2]));
	else if (ac >= 2 && (!ft_strcmp(av[1], "-w") || !ft_strcmp(av[1], "-a")))
	{
		if ((home = sh_getenv("HOME")))
			rl_histsave(ft_pathcat(ft_strcpy(buf, home), ".ushst"));
	}
	else if (ac >= 2 && (!ft_strcmp(av[1], "-r")))
	{
		if ((home = sh_getenv("HOME")))
			rl_histload(ft_pathcat(ft_strcpy(buf, home), ".ushst"));
	}
	else if (ac == 1)
		rl_histdump();
	return (EXIT_SUCCESS);
}
