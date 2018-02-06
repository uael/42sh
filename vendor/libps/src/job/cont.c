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

#include "libps/job.h"

inline void		ps_jobcont(t_job *job, int fg)
{
	size_t	i;
	t_proc	*p;

	i = 0;
	while (i < job->procs.len)
	{
		p = job->procs.buf + i++;
		if (p->state == PROC_STOPPED)
			p->state = PROC_CONTINUED;
	}
	ps_jobdebug(job);
	if (fg)
		ps_jobfg(job, 1);
	else
		ps_jobbg(job, 1);
}
