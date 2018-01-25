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

#include "ush/pool.h"

static int				g_io[3] = { 0, 0, 0 };

static inline int			bang(t_bool b, int status)
{
	if (b)
		return (status ? 0 : 1);
	return (status);
}

static inline int			joblayer(t_job **job, int fg)
{
	size_t	i;
	t_proc	*proc;

	if (!(*job)->procs.len)
		return (EXIT_FAILURE);
	if (!(*job)->procs.buf->pid)
	{
		return (bang((*job)->bang,
			(*job)->procs.buf[(*job)->procs.len - 1].status));
	}
	*job = sh_poolqueue(*job);
	if (fg)
		return (bang((*job)->bang, sh_jobfg(*job, 0)));
	sh_jobbg(*job, (int)(i = 0));
	ft_putf(STDIN_FILENO, "[%d] ", (*job)->idx + 1);
	while (i < (*job)->procs.len)
	{
		proc = (*job)->procs.buf + i++;
		ft_putf(STDIN_FILENO, i < (*job)->procs.len ? "%d " : "%d",
			proc->pid);
	}
	ft_putf(STDIN_FILENO, "\n");
	return (bang((*job)->bang, 0));
}

static inline int			jobfork(t_job *job, t_proc *p, t_bool piped, int fg)
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

static inline int			jobnext(t_job **job, int fg)
{
	t_job	*next;
	int		st;

	g_shstatus = joblayer(job, fg);
	if (!(!g_shinteract || fg) || !(((*job)->andor == ANDOR_OR && g_shstatus) ||
		((*job)->andor == ANDOR_AND && !g_shstatus)))
		return (g_shstatus);
	next = (*job)->next;
	st = sh_joblaunch(&(*job)->next, fg);
	if ((*job)->next->idx >= 0)
	{
		free(next);
		(*job)->next = NULL;
	}
	return (st);
}

int							sh_joblaunch(t_job **job, int fg)
{
	size_t	i;
	t_proc	*proc;
	int		fds[2];

	i = 0;
	ft_memcpy(g_io, STD_FILENOS, 3 * sizeof(int));
	while (i < (*job)->procs.len)
	{
		proc = (*job)->procs.buf + i++;
		sh_jobpipe(*job, i, fds, g_io);
		proc->close = fds[0];
		proc->state = PROC_RUNNING;
		if (jobfork(*job, proc, (t_bool)((*job)->procs.len > 1), fg))
			return (g_shstatus = !(*job)->bang);
		g_io[STDIN_FILENO] != STDIN_FILENO ? close(g_io[STDIN_FILENO]) : 0;
		g_io[STDOUT_FILENO] != STDOUT_FILENO ? close(g_io[STDOUT_FILENO]) : 0;
		g_io[STDIN_FILENO] = fds[0];
	}
	return (jobnext(job, fg));
}
