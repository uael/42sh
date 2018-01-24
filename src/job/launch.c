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
#include "ush/pool.h"

static int				g_io[3] = { 0, 0, 0 };

static inline void		jobpipe(t_job *job, size_t i, int *fds, int *io)
{
	if (i < job->procs.len)
	{
		if (pipe(fds) < 0)
			sh_exit(THROW(WUT), NULL);
		io[STDOUT_FILENO] = fds[1];
	}
	else
	{
		ft_memset(fds, 0, 2 * sizeof(int));
		io[STDOUT_FILENO] = STDOUT_FILENO;
	}
}

static inline int		jobfork(t_job *job, t_proc *p, t_bool piped, int fg)
{
	pid_t	pid;

	p->child = (t_bool)(piped || p->kind == PROC_EXE || p->kind == PROC_SH);
	if (!p->child || !(pid = fork()))
		return (sh_proclaunch(p, job->pgid, g_io, fg));
	else if (pid < 0)
		sh_exit(THROW(WUT), NULL);
	else
	{
		p->pid = pid;
		if (g_shinteract)
		{
			setpgid(pid, job->pgid);
			if (!job->pgid)
				job->pgid = pid;
		}
	}
	return (YEP);
}

static inline int		bang(t_bool b, int status)
{
	if (b)
		return (status ? 0 : 1);
	return (status);
}

static int				sh_joblayer(t_job *job, int fg)
{
	size_t	i;
	t_proc	*proc;

	if (!job->procs.len)
		return (EXIT_FAILURE);
	if (!job->procs.buf->pid)
		return (bang(job->bang, job->procs.buf[job->procs.len - 1].status));
	job = sh_poolqueue(job);
	if (fg)
		return (bang(job->bang, sh_jobfg(job, 0)));
	sh_jobbg(job, (int)(i = 0));
	ft_putf(STDOUT_FILENO, "[%d] ", 1);
	while (i < job->procs.len)
	{
		proc = job->procs.buf + i++;
		ft_putf(STDOUT_FILENO, i < job->procs.len ? "%d " : "%d",
			proc->pid);
	}
	ft_putf(STDOUT_FILENO, "\n");
	return (bang(job->bang, 0));
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
	while (i < job->procs.len)
	{
		proc = job->procs.buf + i++;
		jobpipe(job, i, fds, g_io);
		proc->close = fds[0];
		proc->state = PROC_RUNNING;
		if (jobfork(job, proc, (t_bool)(job->procs.len > 1), fg))
			return (g_shstatus = !job->bang);
		if (g_io[STDIN_FILENO] != STDIN_FILENO)
			close(g_io[STDIN_FILENO]);
		if (g_io[STDOUT_FILENO] != STDOUT_FILENO)
			close(g_io[STDOUT_FILENO]);
		g_io[STDIN_FILENO] = fds[0];
	}
	g_shstatus = sh_joblayer(job, fg);
	if (!(!g_shinteract || fg) || !((job->andor == ANDOR_OR && g_shstatus) ||
		(job->andor == ANDOR_AND && !g_shstatus)))
		return (g_shstatus);
	return (sh_joblaunch(job->next, fg));
}
