/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi/unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 11:53:36 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bi.h"
#include "msh/env.h"

#define N_UNSET COLOR_RED COLOR_BOLD "unset: " COLOR_RESET

inline int	sh_bi_unsetenv(t_sh *sh, int ac, char **av, t_job *out)
{
	int	i;
	int	fst;

	(void)out;
	if (ac < 2)
		return (sh_bi_retf(sh, NOP, N_UNSET"%e\n", EINVAL));
	i = 0;
	fst = YEP;
	while (++i < ac)
		if (ft_strchr(av[i], '='))
			return (sh_bi_retf(sh, NOP, N_UNSET"%s\n", "Syntax error"));
		else if (!sh_unsetenv(&sh->env, av[i], 1))
			sh_bi_retf(sh, (fst = NOP), N_UNSET"%s: Environ not fount\n",
				av[i]);
	return (fst);
}
