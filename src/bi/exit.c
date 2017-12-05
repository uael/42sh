/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 16:21:12 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"

#define M_NREQ "Numeric argument required"

inline t_st	sh_bi_exit(t_sh *sh, int ac, char **av, char **env)
{
	size_t	i;
	size_t	j;
	char	*a;

	(void)env;
	if (ac > 2)
		return (ft_retf(NOK, "%s: %e\n", "exit", E2BIG));
	if (ac < 2)
		exit(sh->st);
	a = av[1];
	if (!(i = ft_strlen(a)) || i > 19)
		ft_fatal(NOK, NULL, NULL, "exit: %s, got '%s' instead\n", M_NREQ, a);
	j = 0;
	while (j < i)
		if (!ft_isdigit(a[j]) && !ft_isspace(a[j]))
			ft_fatal(NOK, NULL, NULL, "exit: %s, got '%s' instead\n", M_NREQ, a);
		else
			j++;
	exit((int)ft_atoi(a));
}
