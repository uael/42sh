/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool/mark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "ush/pool.h"

static void		noprint(t_bool *print)
{
	if (!*print)
		ft_putc(STDIN_FILENO, '\n');
	*print = 1;
}

static void		jobfini(t_job *job)
{
	if (job->bg)
	{
		g_shstatus = job->procs.buf[job->procs.len - 1].status;
		if (job->bang)
			g_shstatus = g_shstatus ? 0 : 1;
		if ((job->andor == ANDOR_OR && g_shstatus) ||
			(job->andor == ANDOR_AND && !g_shstatus))
			sh_joblaunch(job->next, !job->bg);
	}
	sh_jobdtor(job);
}

static void		jobstatus(t_bool *print)
{
	size_t	i;
	t_job	*job;

	i = 0;
	while (i < g_pool->len)
		if (sh_jobcompleted(job = g_pool->jobs + i++))
		{
			if (job->bg)
				noprint(print);
			sh_jobdebug(job);
			jobfini(job);
			if (--i != --g_pool->len)
				ft_memmove(g_pool->jobs + i, g_pool->jobs + i + 1,
					sizeof(t_job) * (g_pool->len - i));
		}
		else if (sh_jobstopped(job) && !job->notified)
		{
			job->bg = 1;
			if (!*print)
				ft_puts(STDIN_FILENO, "\r\x1b[0K^Z\n");
			*print = 1;
			sh_jobdebug(job);
			job->notified = 1;
		}
}

inline void		sh_poolnotify(void)
{
	pid_t	pid;
	int		status;
	t_bool	print;

	if (!g_pool)
		return ;
	while (1)
	{
		while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG)) < 0)
			if (errno != EINTR)
				break ;
		if (sh_poolmark(pid, status))
			break ;
	}
	print = 0;
	jobstatus(&print);
	if (print)
		rl_reprint();
}

inline void		sh_poolclean(void)
{
	size_t	i;
	t_job	*job;

	i = 0;
	while (i < g_pool->len)
		if (sh_jobcompleted(job = g_pool->jobs + i++))
		{
			jobfini(job);
			if (--i != --g_pool->len)
				ft_memmove(g_pool->jobs + i, g_pool->jobs + i + 1,
					sizeof(t_job) * (g_pool->len - i));
		}
}
