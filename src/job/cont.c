/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/cont.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/job.h"

inline void		sh_jobcont(t_job *job, int fg)
{
	size_t	i;
	t_proc	*p;

	i = 0;
	while (i < job->processes.len)
	{
		p = job->processes.buf + i++;
		p->state = p->state == PROC_CONTINUED && fg ?
			PROC_RUNNING : PROC_CONTINUED;
	}
	sh_jobdebug(job);
	job->notified = 0;
	if (fg)
		sh_jobfg(job, 1);
	else
		sh_jobbg(job, 1);
}
