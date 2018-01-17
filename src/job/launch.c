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
	if (i < job->pipeline.len)
	{
		if (pipe(fds) < 0)
			sh_exit(THROW(WUT), NULL);
		io[STDOUT_FILENO] = fds[1];
	}
}

static inline void	jobfork(t_job *job, t_proc *proc, t_bool piped, int fg)
{
	pid_t	pid;

	if ((!piped && proc->kind == PROC_FN) || (pid = fork()))
		sh_proclaunch(proc, job, fg);
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

}

void				sh_joblaunch(t_job *job, int fg)
{
	size_t	i;
	t_proc	*proc;
	int		fds[2];
	int		io[3];

	ft_memcpy(io, job->io, 3 * sizeof(int));
	i = 0;
	while (i < job->pipeline.len)
	{
		proc = job->pipeline.buf + i++;
		jobpipe(job, i, fds, io);
		jobfork(job, proc, (t_bool)(i < job->pipeline.len), fg);
		if (io[STDIN_FILENO] != job->io[STDIN_FILENO])
			close(io[STDIN_FILENO]);
		if (io[STDOUT_FILENO] != job->io[STDOUT_FILENO])
			close(io[STDOUT_FILENO]);
		io[STDIN_FILENO] = fds[0];
	}
	sh_jobdebug(job, "launched");
	if (!g_shinteract)
		sh_jobwait(job);
	else if (fg)
		sh_jobfg(job, 0);
	else
		sh_jobbg(job, 0);
}
