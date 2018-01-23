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

#include "ush/job.h"

inline void		sh_jobctor(t_job *job)
{
	ft_memset(job, 0, sizeof(t_job));
	ft_vecctor((t_vec *)&job->procs, sizeof(t_proc));
}

inline void		sh_jobdtor(t_job *job)
{
	ft_vecdtor((t_vec *)&job->procs, (t_dtor)sh_procdtor);
	if (job->next)
	{
		free(job->next);
		job->next = NULL;
	}
}
