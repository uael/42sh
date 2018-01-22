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
#include "ush/pool.h"

inline void		sh_jobwait(t_job *job)
{
	int		status;
	pid_t	pid;
	//t_job	*new;

	while (1)
	{
		while ((pid = waitpid(-job->pgid, &status, WUNTRACED)) < 0)
			if (errno != EINTR)
				break ;
		if (sh_jobmark(job, pid, status) || sh_jobstopped(job)
			|| sh_jobcompleted(job))
			break ;
	}
	/*if (sh_jobstopped(job))
	{
		ft_putc(STDIN_FILENO, '\n');
		sh_jobdebug(new = sh_pooladd(job));
		if (new != job)
			sh_jobctor(job);
		return ;
	}*/
}
