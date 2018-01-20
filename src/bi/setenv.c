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

#define M_SYNER "Syntax error"
#define M_ENOID "not an identifier"
#define N_EXPORT COLOR_RED COLOR_BOLD "setenv: " COLOR_RESET

inline int	sh_bisetenv(int ac, char **av, char **env)
{
	if (ac == 1)
		return (sh_bienv(ac, av, env));
	(void)env;
	if (ac < 2 || ac > 3 || !av[1] ||
		ft_strchr(av[1], '=') ||
		(ac == 3 && ft_strchr(av[2], '=')))
		return (ft_retf(NOP, N_EXPORT"%s\n", M_SYNER));
	if (!ft_isalpha(*av[1]))
		return (ft_retf(NOP, N_EXPORT"%s: %s\n", av[1], M_ENOID));
	sh_setenv(av[1], ac == 3 ? av[2] : 0);
	return (YEP);
}
