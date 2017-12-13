/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi/setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 09:27:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bi.h"
#include "msh/env.h"

#define M_SYNER "Syntax error"
#define M_ENOID "not an identifier"
#define N_EXPORT COLOR_RED COLOR_BOLD "export: " COLOR_RESET

inline int	sh_bi_setenv(t_sh *sh, int ac, char **av, t_job *out)
{
	if (ac == 1)
		return (sh_bi_env(sh, ac, av, out));
	if (ac < 2 || ac > 3 || !av[1] ||
		ft_strchr(av[1], '=') ||
		(ac == 3 && ft_strchr(av[2], '=')))
		return (sh_bi_retf(sh, NOP, N_EXPORT"%s\n", M_SYNER));
	if (!ft_isalpha(*av[1]))
		return (sh_bi_retf(sh, NOP, N_EXPORT"%s: %s\n", av[1], M_ENOID));
	sh_setenv(&sh->env, av[1], ac == 3 ? av[2] : 0);
	return (YEP);
}
