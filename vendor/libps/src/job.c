/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

inline void		ps_jobctor(t_job *job)
{
	ft_memset(job, 0, sizeof(t_job));
	ft_vecctor((t_vec *)&job->procs, sizeof(t_proc));
}

inline void		ps_jobdtor(t_job *job)
{
	ft_vecdtor((t_vec *)&job->procs, (t_dtor)ps_procdtor);
	if (job->next)
	{
		ps_jobdtor(job->next);
		free(job->next);
		job->next = NULL;
	}
}

inline t_job	*ps_jobnext(t_job *job, t_job *right, t_andor andor)
{
	job->andor = andor;
	job->next = ft_memdup(right, sizeof(t_job));
	job = job->next;
	return (job);
}
