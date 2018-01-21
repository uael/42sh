/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "ush/proc.h"

static inline pid_t	prepare(t_proc *proc, pid_t pgid, int *io, int fg)
{
	pid_t pid;

	pid = getpid();
	if (ft_dup2std(io, proc->src) ||
		sh_redirect(&proc->redirs, pid == g_shpgid ? proc->scope : NULL))
	{
		if (pid == g_shpgid)
			exit(EXIT_FAILURE);
		return (WUT);
	}
	if (pid != g_shpgid && g_shinteract)
	{
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (fg)
			tcsetpgrp(STDIN_FILENO, pgid);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
	}
	return (pid);
}

int					sh_proclaunch(t_proc *proc, pid_t pgid, int *io, int fg)
{
	pid_t		pid;

	if ((pid = prepare(proc, pgid, io, fg)) < 0)
		return (NOP);
	if (proc->kind == PROC_SH)
		return (sh_procshlaunch(proc, pid));
	else if (proc->kind == PROC_FN)
		return (sh_procfnlaunch(proc, pid));
	else if (proc->kind == PROC_CNF)
		return (sh_proccnflaunch(proc));
	else if (proc->kind == PROC_EXE)
	{
		execve(proc->u.exe, proc->argv, proc->envv);
		return (sh_exit(THROW(WUT), NULL));
	}
	return (YEP);
}
