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

#define JOBS "jobs: "

inline int	sh_bijobs(int ac, char **av, char **env)
{
	ssize_t	i;
	t_job	*job;

	(void)env;
	i = 0;
	ps_poolnotify();
	if (ac == 1)
		while ((size_t)i < ps_poollen())
			ps_jobdebug(ps_poolget((size_t)i++));
	else
		while (*++av)
		{
			i = ft_atoi(*av);
			if (ft_strlen(*av) != ft_intlen(i, 10) ||
				!(job = ps_poolget((size_t)i)))
				ft_putf(STDERR_FILENO, JOBS"%s: job not found\n", *av);
			else
				ps_jobdebug(job);
		}
	return (EXIT_SUCCESS);
}
