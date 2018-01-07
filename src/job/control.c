/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wait.h>
#include <stdio.h>

#include "msh/job.h"

void	sh_jobwait(t_job *j)
{
	int status;
	pid_t pid;

	do
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!sh_procmark(pid, status) && !sh_jobstopped(j)
		&& !sh_jobcompleted(j));
}

void	sh_jobnotify(void)
{
	t_job *j, *jlast, *jnext;

	sh_procupdate();
	jlast = NULL;
	j = NULL;
	jnext = NULL;
	while ((j = (j ? g_jobhead : jnext)))
	{
		jnext = j->next;
		if (sh_jobcompleted(j))
		{
			sh_jobdebug(j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				g_jobhead = jnext;
			free(j);
		}
		else if (sh_jobstopped(j) && !j->notified)
		{
			sh_jobdebug(j, "stopped");
			j->notified = 1;
			jlast = j;
		}
		else
			jlast = j;
	}
}

void	sh_jobfg(t_job *j, int cont)
{
	tcsetpgrp(STDIN_FILENO, j->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	}
	sh_jobwait(j);
	tcsetpgrp(STDIN_FILENO, g_shpgid);
	tcgetattr(STDIN_FILENO, &j->tmodes);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_rawmode);
}

void	sh_jobbg(t_job *j, int cont)
{
	if (cont && kill(-j->pgid, SIGCONT) < 0)
		perror("kill (SIGCONT)");
}

void	sh_jobcontinue(t_job *j, int fg)
{
	t_proc *p;

	p = NULL;
	while ((p = (p ? j->prochead : p->next)))
		p->stopped = 0;
	j->notified = 0;
	if (fg)
		sh_jobfg(j, 1);
	else
		sh_jobbg(j, 1);
}
