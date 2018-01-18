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

#include "ush/proc.h"
#include "ush/job.h"

static inline void	procfg(pid_t pgid, int fg)
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
}

static inline int	porcio(t_proc *proc)
{
	int io[3];

	ft_memcpy(io, proc->io, 3 * sizeof(int));
	if (io[STDIN_FILENO] >= 0 && io[STDIN_FILENO] != STDIN_FILENO)
	{
		if (dup2(io[STDIN_FILENO], STDIN_FILENO) < 0 ||
			close(io[STDIN_FILENO]))
			return (THROW(WUT));
	}
	if (io[STDOUT_FILENO] >= 0 && io[STDOUT_FILENO] != STDOUT_FILENO)
	{
		if (dup2(io[STDOUT_FILENO], STDOUT_FILENO) < 0 ||
			close(io[STDOUT_FILENO]))
			return (THROW(WUT));
	}
	if (io[STDERR_FILENO] >= 0 && io[STDERR_FILENO] != STDERR_FILENO)
	{
		if (dup2(io[STDERR_FILENO], STDERR_FILENO) < 0 ||
			close(io[STDERR_FILENO]))
			return (THROW(WUT));
	}
	return (YEP);
}

static inline void	procredir(t_proc *proc)
{
	size_t	i;
	t_redir	*redir;

	i = 0;
	while (i < proc->redirs.len)
	{
		redir = proc->redirs.buf + i;
		if (redir->to < 0)
			close(redir->from);
		else if (dup2(redir->to, redir->from) < 0 || close(redir->to))
			sh_exit(THROW(WUT), NULL);
	}
}

static inline int	avcount(char **av)
{
	char **beg;

	if (!av || !*av)
		return (0);
	beg = av;
	while (*av)
		++av;
	return ((int)(av - beg));
}

void				sh_proclaunch(t_proc *proc, pid_t pgid, int fg)
{
	procfg(pgid, fg);
	if (porcio(proc))
		return ;
	procredir(proc);
	if (proc->kind == PROC_FN)
		proc->u.fn(avcount(proc->argv), proc->argv, proc->envv);
	else if (proc->kind == PROC_EXE)
	{
		execve(proc->argv[0], proc->argv, proc->envv);
		sh_exit(THROW(WUT), NULL);
	}
}
