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
	int		status;
	pid_t	pid;
	size_t	i;
	t_bool	child;

	i = 0;
	child = 0;
	while (i < job->processes.len)
		if (job->processes.buf[i++].pid > 0)
			child = 1;
	if (!child)
		return ;
	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED)) < 0)
		if (errno != EINTR)
			break ;
	while (!sh_jobmark(job, pid, status) && !sh_jobstopped(job)
		&& !sh_jobcompleted(job))
		while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED)) < 0)
			if (errno != EINTR)
				break ;
}
