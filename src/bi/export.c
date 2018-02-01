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

inline int				sh_biexport(int ac, char **a, char **envv)
{
	char	*val;
	int		i;

	i = 0;
	if (ac == 1)
		return (sh_vardump(envv));
	while (++i < ac)
		if (*a[i] == '=')
			return (ft_retf(EXIT_FAILURE, "%s: bad assignment\n", a[i]));
		else if ((val = ft_strchr(a[i], '=')))
			if (!sh_isname(a[i]))
				return (ft_retf(EXIT_FAILURE, "%s: not an identifier\n", a[i]));
			else
			{
				*val = '\0';
				export(a[i], ++val, envv);
			}
		else if (sh_isname(a[i]))
			export(a[i], NULL, envv);
		else
			return (ft_retf(EXIT_FAILURE, "%s: Invalid argument\n", a[i]));
	return (EXIT_SUCCESS);
}
