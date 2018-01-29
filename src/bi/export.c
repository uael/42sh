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

static inline void		export(char *var, char *val)
{
	char *local;

	if ((local = sh_varget(var, NULL)) && !val)
		val = local;
	sh_setenv(var, val);
	if (local)
		sh_varset(var, NULL);
}

inline int				sh_biexport(int ac, char **av, char **env)
{
	char	*val;
	int		i;

	(void)env;
	i = 0;
	while (++i < ac)
		if (*av[i] == '=')
			ft_retf(EXIT_FAILURE, "%s: bad assignment\n", av[i]);
		else if ((val = ft_strchr(av[i], '=')))
			if (!sh_isname(av[i]))
				ft_retf(EXIT_FAILURE, "%s: bad assignment\n", av[i]);
			else
			{
				*val = '\0';
				export(av[i], ++val);
			}
		else if (sh_isname(av[i]))
			export(av[i], NULL);
		else
			ft_retf(EXIT_FAILURE, "%s: bad assignment\n", av[i]);
	return (EXIT_SUCCESS);
}
