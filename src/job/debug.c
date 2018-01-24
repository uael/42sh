/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/job.h"
#include "ush/pool.h"

static char		*g_strst[] =
{
	[PROC_RUNNING] = "running\t",
	[PROC_STOPPED] = "suspended\t",
	[PROC_CONTINUED] = "continued\t",
	[PROC_COMPLETED] = "done\t\t"
};

inline void		sh_jobdebug(t_job *job)
{
	size_t i;
	t_proc *proc;

	if (!job->procs.len || !job->bg)
		return ;
	ft_putf(STDOUT_FILENO, "[%d]  + ", job->idx + 1);
	i = 0;
	while (i < job->procs.len)
	{
		proc = job->procs.buf + i++;
		if (i != 1)
			ft_putf(STDOUT_FILENO, "       ");
		ft_putf(STDOUT_FILENO, "%d %s\n", proc->pid, g_strst[proc->state]);
	}
}
