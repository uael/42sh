/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 16:23:22 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"
#include "msh/env.h"

#define M_SYNER "Syntax error"
#define M_ENOID "not an identifier"

inline t_st	sh_bi_setenv(t_sh *sh, int ac, char **av, char **env)
{
	if (ac == 1)
		return (sh_bi_env(sh, ac, av, env));
	if (ac < 2 || ac > 3 || !av[1] ||
		ft_strchr(av[1], '=') ||
		(ac == 3 && ft_strchr(av[2], '=')))
		return (ft_retf(NOK, "%s: %s\n", "export", M_SYNER));
	if (!ft_isalpha(*av[1]))
		return (ft_retf(NOK, "%s: %s '%s'\n", "export", M_ENOID, av[1]));
	return (sh_setenv(&sh->env, av[1], ac == 3 ? av[2] : 0));
}
