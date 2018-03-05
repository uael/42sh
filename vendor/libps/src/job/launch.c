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

#include "../ps.h"

static inline int		jobbg(t_job *job)
{
	size_t	i;
	t_proc	*proc;
	int		st;

	i = 0;
	st = ps_jobbg(job, (int)i);
	if (job->bang)
		st = st ? 0 : 1;
	ft_putf(STDIN_FILENO, "[%d] ", job->idx + 1);
	while (i < job->procs.len)
	{
		proc = job->procs.buf + i++;
		ft_putf(STDIN_FILENO, i < job->procs.len ? "%d " : "%d", proc->pid);
	}
	ft_putf(STDIN_FILENO, "\n");
	return (st);
}

static inline int		jobnext(t_job *job, int st)
{
	t_job	*next;
	t_andor	andor;

	if (job->bang)
		st = st ? 0 : 1;
	andor = job->andor;
	while (andor != ANDOR_NONE)
	{
		next = job->next;
		job->next = NULL;
		ps_jobdtor(job);
		ft_memcpy(job, next, sizeof(t_job));
		free(next);
		if ((andor == ANDOR_OR && st) || (andor == ANDOR_AND && !st))
			break ;
		andor = job->andor;
	}
	if (!andor)
	{
		ps_jobdtor(job);
		return (st);
	}
	return (ps_joblaunch(job, 1));
}

static inline int		output(char *data)
{
	ft_puts(STDOUT_FILENO, data);
	return (EXIT_SUCCESS);
}

static inline t_proc	*jobpeek(t_job *job, size_t *i)
{
	t_proc *proc;
	t_proc in;

	proc = job->procs.buf + (*i)++;
	if (proc->in)
	{
		ps_procfn(&in, (t_proccb *)output, (t_dtor)free, proc->in);
		proc->in = NULL;
		proc = (t_proc *)ft_vecput((t_vec *)&job->procs, *i - 1);
		*proc = in;
	}
	return (proc);
}

int						ps_joblaunch(t_job *job, int fg)
{
	size_t	i;
	t_proc	*prc;
	int		fds[2];
	int		io[3];

	i = 0;
	ft_memcpy(io, STD_FILENOS, 3 * sizeof(int));
	while (i < job->procs.len)
	{
		prc = jobpeek(job, &i);
		ps_jobpipe(job, i, fds, io);
		prc->close = fds[0];
		if (!prc->child)
			prc->child = (t_bool)(job->procs.len > 1 || prc->kind == PROC_EXE);
		if (ps_procfork(prc, &job->pgid, io, fg))
			return (ft_dtor(!job->bang, (t_dtor)ps_jobdtor, job, NULL));
		io[STDIN_FILENO] != STDIN_FILENO ? close(io[STDIN_FILENO]) : 0;
		io[STDOUT_FILENO] != STDOUT_FILENO ? close(io[STDOUT_FILENO]) : 0;
		io[STDIN_FILENO] = fds[0];
	}
	if (!job->procs.len)
		return (jobnext(job, EXIT_FAILURE));
	else if (!job->procs.buf->pid)
		return (jobnext(job, job->procs.buf[job->procs.len - 1].status));
	return (fg ? jobnext(job, ps_jobfg(job, 0)) : jobbg(job));
}
