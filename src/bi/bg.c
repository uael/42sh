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

#define BG COLOR_BRED"bg: "COLOR_RESET

inline int	sh_bibg(int ac, char **av, char **env)
{
	ssize_t	i;
	t_job	*job;

	(void)env;
	if (!g_pool || !g_pool->len)
		return (ft_retf(EXIT_FAILURE, BG"no current job\n"));
	if (ac != 1)
		while (*++av)
			(job = sh_poolfind((pid_t)ft_atoi(*av)))
				? sh_jobcont(job, 0)
				: ft_putf(STDERR_FILENO, BG"%s: job not found\n", *av);
	else
	{
		i = g_pool->len;
		while (--i >= 0)
			if (sh_jobstopped(job = g_pool->jobs + i))
			{
				sh_jobcont(job, 0);
				return (EXIT_SUCCESS);
			}
		return (ft_retf(EXIT_FAILURE, BG"no current job\n"));
	}
	return (EXIT_SUCCESS);
}
