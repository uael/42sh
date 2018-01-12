/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wait.h>
#include <stdio.h>

#include "ush/proc.h"
#include "ush/job.h"

void	sh_proclaunch(t_proc *p, pid_t pgid, int *io, int fg)
{
	pid_t pid;

	if (g_shinteract)
	{
		pid = getpid();
		if (pgid == 0) pgid = pid;
		setpgid(pid, pgid);
		if (fg)
			tcsetpgrp(STDIN_FILENO, pgid);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	if (io[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(io[STDIN_FILENO], STDIN_FILENO);
		close(io[STDIN_FILENO]);
	}
	if (io[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(io[STDOUT_FILENO], STDOUT_FILENO);
		close(io[STDOUT_FILENO]);
	}
	if (io[STDERR_FILENO] != STDERR_FILENO)
	{
		dup2(io[STDERR_FILENO], STDERR_FILENO);
		close(io[STDERR_FILENO]);
	}
	execvp(p->argv[0], p->argv);
	perror("execvp");
	exit(1);
}

int		sh_procmark(pid_t pid, int status)
{
	t_job *j;
	t_proc *p;

	if (pid > 0)
	{
		j = NULL;
		while ((j = (j ? g_jobhead : j->next)) &&
			!(p = NULL))
			while ((p = (p ? j->prochead : p->next)))
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED (status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED (status))
							fprintf(stderr, "%d: Terminated by signal %d.\n",
								(int) pid, WTERMSIG (p->status));
					}
					return 0;
				}
		fprintf(stderr, "No child process %d.\n", pid);
		return -1;
	}
	else if (pid == 0 || errno == ECHILD)
		return -1;
	else
	{
		perror("waitpid");
		return -1;
	}
}

void	sh_procupdate(void)
{
	int status;
	pid_t pid;

	do
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!sh_procmark(pid, status));
}
