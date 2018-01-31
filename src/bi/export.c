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

static inline void		export(char *var, char *val, char **envv)
{
	char *local;

	if ((local = sh_varget(var, envv)) && !val)
		val = local;
	if (!val)
		sh_varset(var, "");
	else
	{
		sh_setenv(var, val);
		if (local)
			sh_varset(var, NULL);
	}
}

inline int				sh_biexport(int ac, char **av, char **envv)
{
	char	*val;
	int		i;

	i = 0;
	if (ac == 1)
		return (sh_vardump(envv));
	while (++i < ac)
		if (*av[i] == '=')
			return (ft_retf(EXIT_FAILURE, "%s: bad assignment\n", av[i]));
		else if ((val = ft_strchr(av[i], '=')))
			if (!sh_isname(av[i]))
				return (ft_retf(EXIT_FAILURE, "%s: not an identifier\n", av[i]));
			else
			{
				*val = '\0';
				export(av[i], ++val, envv);
			}
		else if (sh_isname(av[i]))
			export(av[i], NULL, envv);
		else
			return (ft_retf(EXIT_FAILURE, "%s: Invalid argument\n", av[i]));
	return (EXIT_SUCCESS);
}
