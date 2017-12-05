/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 16:23:22 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"
#include "msh/env.h"

inline t_st	sh_bi_unsetenv(t_sh *sh, int ac, char **av, char **env)
{
	t_st	st;
	int		i;
	t_st	fst;

	(void)env;
	if (ac < 2)
		return (ft_retf(NOK, "%s: %e\n", "unset", EINVAL));
	i = 0;
	fst = OK;
	while (++i < ac)
		if (ft_strchr(av[i], '='))
			return (ft_retf(NOK, "%s: %s\n", "unset", "Syntax error"));
		else if (ISE(st = sh_unsetenv(&sh->env, av[i], 1)))
			return (st);
		else if (ST_NOK(st))
			ft_retf((fst = NOK), "%s: %s '%s'\n",
					"unset", "Environ not fount", av[i]);
	return (fst);
}
