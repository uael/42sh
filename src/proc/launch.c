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

static inline pid_t	prepare(t_proc *prc, pid_t pgid, int *io, int fg)
{
	pid_t pid;

	pid = getpid();
	prc->close != STDIN_FILENO && prc->close != io[0] ? close(prc->close) : 0;
	if (ft_dup2std(io, prc->src) ||
		sh_redirect(&prc->redirs, prc->child ? NULL : prc->scope))
	{
		prc->child ? 0 : ft_dup2std(prc->scope, STD_FILENOS);
		if (prc->child)
			exit(EXIT_FAILURE);
		prc->status = EXIT_FAILURE;
		return (WUT);
	}
	if (prc->child && g_shinteract)
	{
		setpgid(0, pgid);
		fg ? tcsetpgrp(STDIN_FILENO, pgid) : 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
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
		return (sh_procfnlaunch(proc));
	else if (proc->kind == PROC_CNF)
		return (sh_proccnflaunch(proc));
	else if (proc->kind == PROC_BOOL)
		return (sh_procboollaunch(proc));
	else if (proc->kind == PROC_EXE)
	{
		execve(proc->u.exe, proc->argv, proc->envv);
		return (sh_exit(EXIT_FAILURE, NULL));
	}
	return (YEP);
}
