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

static inline pid_t	procfg(pid_t pgid, int fg)
{
	pid_t pid;

	if ((pid = getpid()) != g_shpgid && g_shinteract)
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
		signal(SIGCHLD, SIG_DFL);
	}
	return (pid);
}

static inline int	porcio(int *io, int *src)
{
	if (io[STDIN_FILENO] >= 0 && io[STDIN_FILENO] != STDIN_FILENO)
	{
		if (dup2(io[STDIN_FILENO], src[STDIN_FILENO]) < 0 ||
			close(io[STDIN_FILENO]))
			return (THROW(WUT));
	}
	if (io[STDOUT_FILENO] >= 0 && io[STDOUT_FILENO] != STDOUT_FILENO)
	{
		if (dup2(io[STDOUT_FILENO], src[STDOUT_FILENO]) < 0 ||
			close(io[STDOUT_FILENO]))
			return (THROW(WUT));
	}
	if (io[STDERR_FILENO] >= 0 && io[STDERR_FILENO] != STDERR_FILENO)
	{
		if (dup2(io[STDERR_FILENO], src[STDERR_FILENO]) < 0 ||
			close(io[STDERR_FILENO]))
			return (THROW(WUT));
	}
	return (YEP);
}

static inline int	procredir(t_proc *proc, pid_t pid)
{
	size_t	i;
	t_redir	*redir;

	i = 0;
	while (i < proc->redirs.len)
	{
		redir = proc->redirs.buf + i++;
		if (pid == g_shpgid && redir->from >= 0 && redir->from <= 2 &&
			proc->scope[redir->from] < 0)
			proc->scope[redir->from] = dup(redir->from);
		if (redir->to < 0)
			close(redir->from);
		else if (dup2(redir->to, redir->from) < 0 || close(redir->to))
			return (THROW(WUT));
	}
	return (YEP);
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

static int	exhdl(int rcode, void *arg)
{
	(void)arg;
	errno = 0;
	return (rcode);
}

int					sh_proclaunch(t_proc *proc, pid_t pgid, int *io, int fg)
{
	pid_t		pid;
	t_ex_hdl	dfl;

	pid = procfg(pgid, fg);
	if (porcio(io, proc->src) || procredir(proc, pid))
	{
		if (pid == g_shpgid)
			exit(EXIT_FAILURE);
		return (NOP);
	}
	if (proc->kind == PROC_SH)
	{
		g_shinteract = 0;
		g_shpgid = pid;
		sh_eval(-1, &proc->u.sh.toks, &proc->u.sh.ln);
		proc->status = g_shstatus;
		return (sh_exit(g_shstatus, NULL));
	}
	else if (proc->kind == PROC_FN)
	{
		ft_exbind(EXALL, ft_exhdl(exhdl, NULL), &dfl);
		proc->status = proc->u.fn(avcount(proc->argv), proc->argv, proc->envv);
		ft_exbind(EXALL, dfl, NULL);
		if (pid > 0 && pid != g_shpgid)
			exit(proc->status);
		porcio(proc->scope,
			(int[3]){STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO});
		return (YEP);
	}
	else if (proc->kind == PROC_CMDERR)
	{
		if (proc->u.cmderr.ln)
			sh_synerr(proc->u.cmderr.ln, proc->u.cmderr.it,
				proc->u.cmderr.st == PROC_NORIGHTS ? "%s: permission denied"
					: "%s: Command not found", proc->u.cmderr.exe);
		else
			ft_putf(2, proc->u.cmderr.st == PROC_NORIGHTS ? "%s: permission denied\n"
				: "%s: Command not found\n", proc->u.cmderr.exe);
		exit(proc->u.cmderr.st);
	}
	else if (proc->kind == PROC_EXE)
	{
		execve(proc->argv[0], proc->argv, proc->envv);
		return (sh_exit(THROW(WUT), NULL));
	}
	return (YEP);
}
