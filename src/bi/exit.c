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

#define M_NREQ "Numeric argument required"
#define N_EXIT COLOR_RED COLOR_BOLD "exit: " COLOR_RESET


inline int	sh_bi_exit(int ac, char **av, char **env)
{
    size_t	i;
	size_t	j;
	char	*a;
	int		c;

    (void)env;
    if (ac > 2)
        (ft_retf(128, N_EXIT"%e\n", E2BIG));
    ac < 2 ? sh_exit(g_shstatus, NULL) : 0;
    a = av[1];
    if (!(i = ft_strlen(a)) || i > 19)
		return (ft_retf(128, N_EXIT"%s: %s\n", a, M_NREQ));
	j = 0;
	while (j < i)
		if (!ft_isdigit(a[j]) && !ft_isspace(a[j]))
			return (ft_retf(128, N_EXIT"%s: %s\n", a, M_NREQ));
		else
			j++;
	c = (int)ft_atoi(a);
	if (ft_intlen(c, 10) != ft_strlen(a))
		return (sh_exit(128, NULL));
	return (sh_exit(c > 255 || c < 0 ? 255 : 0, NULL));
}