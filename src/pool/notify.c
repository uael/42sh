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

#include "ush/pool.h"

inline void		sh_poolnotify(void)
{
	size_t	i;
	t_job	*job;
	pid_t	pid;
	int		status;

	if (!g_pool)
		return ;
	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!sh_poolmark(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	i = 0;
	while (i < g_pool->len)
		if (sh_jobcompleted(job = g_pool->jobs + i++))
		{
			sh_jobdebug(job, "completed");
			ft_vecrem((t_vec *)g_pool, i - 1, NULL);
		}
		else if (sh_jobstopped(job) && !job->notified)
		{
			sh_jobdebug(job, "stopped");
			job->notified = 1;
		}
}
