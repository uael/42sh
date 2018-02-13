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

#include "../ps.h"

int		ps_jobstopped(t_job *j)
{
	t_proc	*p;
	size_t	i;
	int		s;

	i = 0;
	s = 0;
	while (i < j->procs.len)
		if ((p = j->procs.buf + i++)->state != PROC_COMPLETED)
		{
			if (p->state != PROC_STOPPED)
				return (0);
			++s;
		}
	return (s > 0);
}

int		ps_jobcompleted(t_job *j)
{
	size_t i;

	i = 0;
	while (i < j->procs.len)
		if ((j->procs.buf + i++)->state != PROC_COMPLETED)
			return (0);
	return (j->next ? ps_jobcompleted(j->next) : 1);
}
