/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi/exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 09:27:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bi.h"

#define M_NREQ "Numeric argument required"
#define N_EXIT COLOR_RED COLOR_BOLD "exit: " COLOR_RESET

inline int	sh_bi_exit(t_sh *sh, int ac, char **av, t_job *out)
{
	size_t	i;
	size_t	j;
	char	*a;

	(void)out;
	if (ac > 2)
		return (sh_bi_retf(sh, NOP, N_EXIT"%e\n", E2BIG));
	if (ac < 2)
		exit(sh->st);
	a = av[1];
	if (!(i = ft_strlen(a)) || i > 19)
		ft_fatal(NOP, NULL, NULL, N_EXIT"%s: %s\n", a, M_NREQ);
	j = 0;
	while (j < i)
		if (!ft_isdigit(a[j]) && !ft_isspace(a[j]))
			ft_fatal(NOP, NULL, NULL, N_EXIT"%s: %s\n", a, M_NREQ);
		else
			j++;
	exit((int)ft_atoi(a));
}
