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

inline void		sh_poolnotify(void)
{
	size_t	i;
	t_job	*job;
	pid_t	pid;
	int		status;
	t_bool	print;

	if (!g_pool)
		return ;
	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG)) < 0)
		if (errno != EINTR)
			break ;
	while (!sh_poolmark(pid, status))
		while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG)) < 0)
			if (errno != EINTR)
				break ;
	i = 0;
	print = 0;
	while (i < g_pool->len)
		if (sh_jobcompleted(job = g_pool->jobs + i++))
		{
			if (!print)
				ft_putf(1, "\n");
			print = 1;
			sh_jobdebug(job);
			if ((job->andor == ANDOR_OR && job->status) ||
				(job->andor == ANDOR_AND && !job->status))
			{
				sh_poolpush(job->next);
				job->next = NULL;
			}
			sh_jobdtor(job);
			if (--i != --g_pool->len)
				ft_memmove(g_pool->jobs + i, g_pool->jobs + i + 1,
					sizeof(t_job) * (g_pool->len - i));
		}
		else if (sh_jobstopped(job) && !job->notified)
		{
			if (!print)
				ft_putf(1, "\n");
			print = 1;
			sh_jobdebug(job);
			job->notified = 1;
		}
	if (print)
		rl_reprint();
}
