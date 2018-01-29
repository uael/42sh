/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/fg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "ush/pool.h"

inline int		sh_jobfg(t_job *job, int cont)
{
	int		st;
	t_job	*bg;

	job->bg = 0;
	if (g_shinteract)
		tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &job->tmodes);
		if (kill(-job->pgid, SIGCONT) < 0)
			sh_err("kill (SIGCONT): %e\n", errno);
	}
	sh_jobwait(job);
	if (g_shinteract)
	{
		tcsetpgrp(STDIN_FILENO, g_shpgid);
		tcgetattr(STDIN_FILENO, &job->tmodes);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shmode);
	}
	if (sh_jobstopped(job))
	{
		bg = sh_poolpush(job);
		if (g_shinteract)
			ft_puts(STDIN_FILENO, "\r\x1b[0K^Z\n");
		sh_jobdebug(bg);
		st = g_shstatus;
		sh_jobctor(job);
	}
	else
		st = job->procs.buf[job->procs.len - 1].status;
	return (st);
}
