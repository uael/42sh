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

#include <ush.h>
#include "ush/proc.h"
#include "ush/job.h"

static int				g_io[3] = { 0, 0, 0 };

static inline void		jobpipe(t_job *job, size_t i, int *fds, int *io)
{
	if (i < job->processes.len)
	{
		if (pipe(fds) < 0)
			sh_exit(THROW(WUT), NULL);
		io[STDOUT_FILENO] = fds[1];
	}
	else
		io[STDOUT_FILENO] = STDOUT_FILENO;
}

static inline int		jobfork(t_job *job, t_proc *proc, t_bool piped, int fg)
{
	pid_t	pid;

	if ((!piped && proc->kind == PROC_FN) || !(pid = fork()))
		return (sh_proclaunch(proc, job->pgid, g_io, fg));
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

static void				sh_joblayer(t_job *job, int fg)
{
	size_t	i;
	t_proc	*proc;

	if (job->processes.buf->pid)
	{
		job = sh_pooladd(job);
		if (!g_shinteract)
			sh_jobwait(job);
		else if (fg)
			sh_jobfg(job, 0);
		else
		{
			sh_jobbg(job, 0);
			ft_putf(STDOUT_FILENO, "[%d] ", 1);
			i = 0;
			while (i < job->processes.len)
			{
				proc = job->processes.buf + i++;
				ft_putf(STDOUT_FILENO, i < job->processes.len ? "%d " : "%d",
					proc->pid);
			}
			ft_putf(STDOUT_FILENO, "\n");
		}
	}
}

int						sh_joblaunch(t_job *job, int fg)
{
	size_t	i;
	t_proc	*proc;
	int		fds[2];

	i = 0;
	g_io[STDIN_FILENO] = STDIN_FILENO;
	g_io[STDOUT_FILENO] = STDOUT_FILENO;
	g_io[STDERR_FILENO] = STDERR_FILENO;
	while (i < job->processes.len)
	{
		proc = job->processes.buf + i++;
		jobpipe(job, i, fds, g_io);
		if (jobfork(job, proc, (t_bool)(job->processes.len > 1), fg))
			return (g_shstatus = !job->bang);
		if (g_io[STDIN_FILENO] != STDIN_FILENO)
			close(g_io[STDIN_FILENO]);
		if (g_io[STDOUT_FILENO] != STDOUT_FILENO)
			close(g_io[STDOUT_FILENO]);
		g_io[STDIN_FILENO] = fds[0];
	}
	sh_joblayer(job, fg);
	if (!(!g_shinteract || fg) || !((job->andor == ANDOR_OR && g_shstatus) ||
		(job->andor == ANDOR_AND && !g_shstatus)))
		return (g_shstatus);
	return (sh_joblaunch(job->next, fg));
}
