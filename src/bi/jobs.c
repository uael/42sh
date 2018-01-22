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

#define JOBS COLOR_BRED"jobs: "COLOR_RESET

inline int	sh_bijobs(int ac, char **av, char **env)
{
	size_t	i;
	t_job	*job;

	(void)env;
	i = 0;
	sh_poolnotify();
	if (!g_pool)
		return (EXIT_SUCCESS);
	if (ac == 1)
		while (i < g_pool->len)
			sh_jobdebug(g_pool->jobs + i++);
	else
		while (*++av)
		{
			if ((job = sh_poolfind((pid_t)ft_atoi(*av))))
				sh_jobdebug(job);
			else
				ft_putf(STDERR_FILENO, JOBS"%s: job not found\n", *av);
		}
	return (EXIT_SUCCESS);
}
