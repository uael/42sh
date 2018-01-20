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

#include "ush/pool.h"

inline int		sh_jobmark(t_job *job, pid_t pid, int status)
{
	size_t	i;
	t_proc	*proc;

	if (pid > 0)
	{
		i = 0;
		while (i < job->processes.len)
			if ((proc = job->processes.buf + i++)->pid == pid)
			{
				if (job->bang)
					job->status = status ? 0 : 1;
				else
					job->status = status;
				return (sh_procmark(proc, status));
			}
		sh_err("No child process %d for gpid %d.\n", pid, job->pgid);
		return (WUT);
	}
	return ((pid == 0 || errno == ECHILD) ? WUT : THROW(WUT));
}
