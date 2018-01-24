/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "ush/job.h"

static inline void	waitchilds(t_job *job)
{
	t_proc	*proc;
	ssize_t	i;
	int		st;

	i = job->procs.len;
	while (--i >= 0)
	{
		if ((proc = job->procs.buf + i)->pid <= 0)
			continue ;
		if (proc->state != PROC_RUNNING && proc->state != PROC_CONTINUED)
			continue ;
		while (waitpid(proc->pid, &st, 0) < 0)
			if (errno != EINTR)
			{
				THROW(WUT);
				break ;
			}
		sh_procmark(proc, st);
		if (job->bg == 0 && proc->status == PROC_STOPPED)
			job->bg = 1;
	}
}

inline void			sh_jobwait(t_job *job)
{
	int		status;
	pid_t	pid;

	if (!g_shinteract)
		return (waitchilds(job));
	while (1)
	{
		while ((pid = waitpid(-job->pgid, &status, WUNTRACED)) < 0)
			if (errno != EINTR)
				break ;
		if (sh_jobmark(job, pid, status) || sh_jobstopped(job)
			|| sh_jobcompleted(job))
			break ;
	}
}
