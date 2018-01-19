/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/proc.h"
#include "ush/job.h"

static inline void	jobpipe(t_job *job, size_t i, int *fds, int *io)
{
	if (i < job->processes.len)
	{
		if (pipe(fds) < 0)
			sh_exit(THROW(WUT), NULL);
		io[STDOUT_FILENO] = fds[1];
	}
	else
		io[STDOUT_FILENO] = job->io[STDOUT_FILENO];
}

static inline int	jobfork(t_job *job, t_proc *proc, t_bool piped, int fg)
{
	pid_t	pid;

	if ((!piped && proc->kind == PROC_FN) || !(pid = fork()))
		return (sh_proclaunch(proc, job->pgid, fg));
	else if (pid < 0)
		sh_exit(THROW(WUT), NULL);
	else
	{
		proc->pid = pid;
		if (g_shinteract)
		{
			if (!job->pgid)
				job->pgid = pid;
			setpgid(pid, job->pgid);
		}
	}
	return (YEP);
}

int				sh_joblaunch(t_job *job, int fg)
{
	size_t	i;
	t_proc	*proc;
	int		fds[2];
	int		io[3];

	i = 0;
	ft_memcpy(io, job->io, 3 * sizeof(int));
	while (i < job->processes.len)
	{
		proc = job->processes.buf + i++;
		jobpipe(job, i, fds, io);
		ft_memcpy(proc->io, io, 3 * sizeof(int));
		if (jobfork(job, proc, (t_bool)(job->processes.len > 1), fg))
			return (job->status = 1);
		if (io[STDIN_FILENO] != job->io[STDIN_FILENO])
			close(io[STDIN_FILENO]);
		if (io[STDOUT_FILENO] != job->io[STDOUT_FILENO])
			close(io[STDOUT_FILENO]);
		io[STDIN_FILENO] = fds[0];
	}
	if (job->processes.buf->pid)
	{
		if (!g_shinteract)
			sh_jobwait(job);
		else if (fg)
			sh_jobfg(job, 0);
		else
			sh_jobbg(job, 0);

	}
	if (!(!g_shinteract || fg) || !((job->andor == ANDOR_OR && !job->status) ||
		(job->andor == ANDOR_AND && job->status)))
		return (job->status);
	return (sh_joblaunch(job->next, fg));
}
