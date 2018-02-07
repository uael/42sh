/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/mark.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ps.h"

inline int		ps_jobmark(t_job *job, pid_t pid, int status)
{
	size_t	i;
	t_proc	*proc;

	if (pid > 0)
	{
		i = 0;
		while (i < job->procs.len)
			if ((proc = job->procs.buf + i++)->pid == pid)
				return (ps_procmark(proc, status));
		return (WUT);
	}
	return ((pid == 0 || errno == ECHILD) ? WUT : THROW(WUT));
}
