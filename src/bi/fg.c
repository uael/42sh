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

#define FG COLOR_BRED"fg: "COLOR_RESET

static void	fg(t_job *job)
{
	size_t	i;
	t_proc	*p;

	if (sh_jobstopped(job))
		sh_jobcont(job, 1);
	else
	{
		i = 0;
		while (i < job->processes.len)
		{
			p = job->processes.buf + i++;
			p->state = PROC_RUNNING;
		}
		sh_jobdebug(job);
		job->notified = 0;
		sh_jobfg(job, 0);
	}
}

inline int	sh_bifg(int ac, char **av, char **env)
{
	ssize_t	i;
	t_job	*job;

	(void)env;
	if (!g_pool || !g_pool->len)
		return (ft_retf(EXIT_FAILURE, FG"no current job\n"));
	if (ac != 1)
		while (*++av)
			(job = sh_poolfind((pid_t)ft_atoi(*av))) ? fg(job)
				: ft_putf(STDERR_FILENO, FG"%s: job not found\n", *av);
	else
	{
		i = g_pool->len;
		while (--i >= 0)
			if ((job = g_pool->jobs + i))
			{
				fg(job);
				return (EXIT_SUCCESS);
			}
		return (ft_retf(EXIT_FAILURE, FG"no current job\n"));
	}
	return (EXIT_SUCCESS);
}
