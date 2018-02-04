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
		g_sh->ppid = pid;
		if (g_sh->tty)
		{
			setpgid(pid, job->pgid);
			if (!job->pgid)
				job->pgid = pid;
		}
	}
	return (YEP);
}

static inline int			jobhelp(t_job *job)
{
	size_t	i;
	t_proc	*proc;
	int		st;

	i = 0;
	st = bang(job->bang, sh_jobbg(job, (int)i));
	ft_putf(STDIN_FILENO, "[%d] ", job->idx + 1);
	while (i < job->procs.len)
	{
		proc = job->procs.buf + i++;
		ft_putf(STDIN_FILENO, i < job->procs.len ? "%d " : "%d", proc->pid);
	}
	ft_putf(STDIN_FILENO, "\n");
	return (st);
}

static inline int			jobnext(t_job *job, int fg)
{
	t_job	*next;
	int		st;

	if (!job->procs.len)
		st = EXIT_FAILURE;
	else if (!job->procs.buf->pid)
		st = bang(job->bang, job->procs.buf[job->procs.len - 1].status);
	else if (!fg)
		return (jobhelp(job));
	else
		st = bang(job->bang, sh_jobfg(job, 0));
	if (!(job->andor == ANDOR_OR && st) && !(job->andor == ANDOR_AND && !st))
	{
		sh_jobdtor(job);
		return (st);
	}
	next = job->next;
	job->next = NULL;
	sh_jobdtor(job);
	ft_memcpy(job, next, sizeof(t_job));
	free(next);
	return (sh_joblaunch(job, fg));
}

int							sh_joblaunch(t_job *job, int fg)
{
	size_t	i;
	t_proc	*proc;
	int		fds[2];

	i = 0;
	job->bg = (t_bool)!fg;
	ft_memcpy(g_io, STD_FILENOS, 3 * sizeof(int));
	while (i < job->procs.len)
	{
		proc = job->procs.buf + i++;
		sh_jobpipe(job, i, fds, g_io);
		proc->close = fds[0];
		proc->state = PROC_RUNNING;
		if (jobfork(job, proc, (t_bool)(job->procs.len > 1), fg))
			return (!job->bang);
		g_io[STDIN_FILENO] != STDIN_FILENO ? close(g_io[STDIN_FILENO]) : 0;
		g_io[STDOUT_FILENO] != STDOUT_FILENO ? close(g_io[STDOUT_FILENO]) : 0;
		g_io[STDIN_FILENO] = fds[0];
	}
	return (jobnext(job, fg));
}
