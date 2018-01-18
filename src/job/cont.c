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

inline void		sh_jobcont(t_job *j, int fg)
{
	size_t i;

	i = 0;
	while (i < j->processes.len)
		(j->processes.buf + i++)->state = PROC_CONTINUED;
	j->notified = 0;
	if (fg)
		sh_jobfg(j, 1);
	else
		sh_jobbg(j, 1);
}
