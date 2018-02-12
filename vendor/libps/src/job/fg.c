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
#include <sys/termios.h>

#include "../ps.h"

inline static int	jobstop(t_job *job)
{
	t_job	*bg;

	bg = ps_poolpush(job);
	if (g_tty)
		ft_puts(STDIN_FILENO, "\r\x1b[0K^Z\n");
	ps_jobdebug(bg);
	ps_jobctor(job);
	return (146);
}

inline int			ps_jobfg(t_job *job, int cont)
{
	int		st;

	job->bg = 0;
	if (g_tty)
		tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &job->tmodes);
		if (kill(-job->pgid, SIGCONT) < 0)
			g_errcb("kill (SIGCONT): %e\n", errno);
	}
	ps_jobwait(job);
	if (g_tty)
	{
		tcsetpgrp(STDIN_FILENO, g_pgid);
		tcgetattr(STDIN_FILENO, &job->tmodes);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_tcmode);
	}
	if (ps_jobstopped(job))
		st = jobstop(job);
	else
		st = job->procs.buf[job->procs.len - 1].status;
	return (st);
}
