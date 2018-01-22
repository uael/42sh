/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/job.h"

int		sh_jobstopped(t_job *j)
{
	t_proc *p;
	size_t i;
	int		s;

	i = 0;
	s = 0;
	while (i < j->processes.len)
		if ((p = j->processes.buf + i++)->state != PROC_COMPLETED)
		{
			if (p->state != PROC_STOPPED)
				return (0);
			++s;
		}

	return (s > 0);
}

int		sh_jobcontinued(t_job *j)
{
	size_t i;

	i = 0;
	while (i < j->processes.len)
		if ((j->processes.buf + i++)->state != PROC_CONTINUED)
			return (0);
	return (1);
}

int		sh_jobcompleted(t_job *j)
{
	size_t i;

	i = 0;
	while (i < j->processes.len)
		if ((j->processes.buf + i++)->state != PROC_COMPLETED)
			return (0);
	return (1);
}
