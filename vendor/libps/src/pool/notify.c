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

#include "../ps.h"

static t_bool	jobnext(t_job *job, int st)
{
	t_job	*next;
	t_andor	andor;

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
		return (1);
	}
	job->bg = 1;
	ps_joblaunch(job, 0);
	return (0);
}

static t_bool	jobfini(t_job *job)
{
	int		st;

	st = !job->procs.len ? 1 : job->procs.buf[job->procs.len - 1].status;
	if (job->bang)
		st = st ? 0 : 1;
	return (jobnext(job, st));
}

inline void		ps_poolnotify(void)
{
	pid_t	pid;
	int		status;
	t_bool	print;
	size_t	i;
	t_job	*job;

	while (1)
	{
		while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG)) < 0)
			if (errno != EINTR)
				break ;
		if (ps_poolmark(pid, status))
			break ;
	}
	print = 0;
	i = 0;
	while (i < ps_poollen())
		if (ps_jobcompleted(job = ps_poolget(i++)))
		{
			print = 1;
			ps_jobdebug(job);
			jobfini(job) ? ps_poolrem(--i, NULL) : 0;
		}
	print ? rl_reprint() : 0;
}
