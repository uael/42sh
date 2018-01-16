/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>

#include "ush/job.h"

t_job	*g_jobhead = NULL;

t_job	*sh_jobfind(pid_t pgid)
{
	t_job *j;

	j = NULL;
	while ((j = (j ? g_jobhead : j->next)))
		if (j->pgid == pgid)
			return j;
	return NULL;
}

int		sh_jobstopped(t_job *j)
{
	t_proc *p;

	p = NULL;
	while ((p = (p ? j->prochead : p->next)))
		if (!p->completed && !p->stopped)
			return 0;
	return 1;
}

int		sh_jobcompleted(t_job *j)
{
	t_proc *p;

	p = NULL;
	while ((p = (p ? j->prochead : p->next)))
		if (!p->completed)
			return 0;
	return 1;
}

void	sh_joblaunch(t_job *j, int fg)
{
	t_proc *p;
	pid_t pid;
	int mypipe[2];
	int io[3];

	ft_memcpy(io, j->io, 3 * sizeof(int));
	p = NULL;
	while ((p = (p ? j->prochead : p->next)))
	{
		if (p->next)
		{
			if (pipe(mypipe) < 0)
			{
				perror("pipe");
				exit(1);
			}
			io[STDOUT_FILENO] = mypipe[1];
		}
		pid = fork();
		if (pid == 0)
			sh_proclaunch(p, j->pgid, io, fg);
		else if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		else
		{
			p->pid = pid;
			if (g_shinteract)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		if (io[STDIN_FILENO] != j->io[STDIN_FILENO])
			close(io[STDIN_FILENO]);
		if (io[STDOUT_FILENO] != j->io[STDOUT_FILENO])
			close(io[STDOUT_FILENO]);
		io[STDIN_FILENO] = mypipe[0];
	}
	sh_jobdebug(j, "launched");
	if (!g_shinteract)
		sh_jobwait(j);
	else if (fg)
		sh_jobfg(j, 0);
	else
		sh_jobbg(j, 0);
}

void	sh_jobdebug(t_job *j, const char *status)
{
	fprintf(stderr, "%ld (%s): %s\n", (long) j->pgid, status, j->command);
}
