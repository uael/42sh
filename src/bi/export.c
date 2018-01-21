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

static void	*sh_getvalue(char *val)
{
	sh_setenv(val, val);
}

inline int 	sh_biexport(int ac, char **av, char **env)
{
	char *val;
	int i;

	(void)env;
	i = 0;
	while (++i < ac)
		if ((val = sh_getenv(av[i])))
		{
			sh_setenv(av[i], val);
			sh_varset(av[i], NULL);
		}
		else if (ft_strcmp(av[i], "="))
			ft_retf(NOP, "bad assignment");
		else if ((val = ft_strchr(av[1], '=')))
			sh_getvalue(val);
		else
			sh_setenv(av[i], "");
	return (YEP);
}
