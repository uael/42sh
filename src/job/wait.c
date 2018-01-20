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

inline void		sh_jobwait(t_job *job)
{
	t_proc	*proc;
	ssize_t	i;
	int		st;

	i = job->processes.len;
	while (--i >= 0)
	{
		if ((proc = job->processes.buf + i)->pid <= 0)
			continue ;
		while (waitpid(proc->pid, &st, 0) < 0)
			if (errno != EINTR)
			{
				THROW(WUT);
				break ;
			}
		sh_procmark(proc, st);
	}
	job->status = job->processes.buf[job->processes.len - 1].status;
	if (job->bang)
		job->status = job->status ? 0 : 1;
}
