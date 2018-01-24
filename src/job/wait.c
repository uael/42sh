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
