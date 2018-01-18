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
			ft_putf(STDOUT_FILENO, "[1]\t+ %d done", job->pgid);
			if (i != g_pool->len--)
				ft_memmove(g_pool->jobs + i - 1, g_pool->jobs + i,
					sizeof(t_job));
		}
		else if (sh_jobstopped(job) && !job->notified)
			job->notified = 1;
}
