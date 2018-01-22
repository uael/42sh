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

#include "ush.h"

inline int	sh_biunset(int ac, char **av, char **env)
{
	int i;

	(void)env;
	i = 0;
	if (ac == 1)
		ft_retf(NOP, "unset: not enough arguments");
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] != 'v' && av[i][1] != 'f')
				ft_retf(NOP, "bad option: -%c", av[i][1]);
			else if (!av[i + 1] || (ft_strcmp(av[i], "-") == 0 && !av[i + 1]))
				ft_retf(NOP, "unset: not enough arguments");
		}
		else if (sh_varget(av[i]))
			sh_varset(av[1], NULL);
	}
	sh_biunsetenv(ac, av, env);
	return (YEP);
}