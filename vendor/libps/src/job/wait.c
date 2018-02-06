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

#include "libps/job.h"

inline void		ps_jobwait(t_job *job)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		while ((pid = waitpid(-job->pgid, &status, WUNTRACED)) < 0)
			if (errno != EINTR)
				break ;
		if (ps_jobmark(job, pid, status) || ps_jobstopped(job)
			|| ps_jobcompleted(job))
			break ;
	}
}
