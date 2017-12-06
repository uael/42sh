/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 10:46:45 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"
#include "msh/env.h"

#define N_UNSET COLOR_RED COLOR_BOLD "unset: " COLOR_RESET

inline t_st	sh_bi_unsetenv(t_sh *sh, int ac, char **av, t_job *out)
{
	t_st	st;
	int		i;
	t_st	fst;

	(void)out;
	if (ac < 2)
		return (sh_bi_retf(sh, NOK, N_UNSET"%e\n", EINVAL));
	i = 0;
	fst = OK;
	while (++i < ac)
		if (ft_strchr(av[i], '='))
			return (sh_bi_retf(sh, NOK, N_UNSET"%s\n", "Syntax error"));
		else if (ISE(st = sh_unsetenv(&sh->env, av[i], 1)))
			return (st);
		else if (ST_NOK(st))
			sh_bi_retf(sh, (fst = NOK), N_UNSET"%s: Environ not fount\n",
				av[i]);
	return (fst);
}
