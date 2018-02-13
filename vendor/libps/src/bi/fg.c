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

#include "../ps.h"

#define FG "fg: "

static void	fg(size_t idx)
{
	size_t	i;
	t_proc	*p;
	t_job	*job;

	if (!ps_poolrem(idx, job = alloca(sizeof(t_job))))
		return ;
	if (ps_jobstopped(job))
		ps_jobcont(job, 1);
	else
	{
		i = 0;
		while (i < job->procs.len)
		{
			p = job->procs.buf + i++;
			p->state = PROC_RUNNING;
		}
		ps_jobdebug(job);
		ps_jobfg(job, 0);
	}
}

inline int	ps_bifg(int ac, char **av, char **env)
{
	ssize_t	i;

	(void)env;
	if (!ps_poollen())
		return (ft_retf(EXIT_FAILURE, FG"no current job\n"));
	if (ac != 1)
		while (*++av)
		{
			i = ft_atoi(*av);
			if (ft_strlen(*av) != ft_intlen(i, 10) || (size_t)i >= ps_poollen())
				ft_putf(STDERR_FILENO, FG"%s: job not found\n", *av);
			else
				fg((size_t)i);
		}
	else
		fg((size_t)ps_poollen() - 1);
	return (EXIT_SUCCESS);
}
