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

	i = 0;
	while (i < j->pipeline.len)
		if ((p = j->pipeline.buf + i++)->state != PROC_COMPLETED &&
			p->state != PROC_STOPPED)
			return (0);
	return (1);
}

int		sh_jobcompleted(t_job *j)
{
	size_t i;

	i = 0;
	while (i < j->pipeline.len)
		if ((j->pipeline.buf + i++)->state != PROC_COMPLETED)
			return (0);
	return (1);
}
