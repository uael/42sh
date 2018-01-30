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

#include <signal.h>

#include "ush/proc.h"

inline void			sh_procctor(t_proc *proc)
{
	ft_memset(proc, 0, sizeof(t_proc));
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, STD_FILENOS, 3 * sizeof(int));
}

inline void			sh_procdtor(t_proc *p)
{
	char **av;

	if ((av = p->argv))
	{
		while (*av)
			free(*av++);
		ft_pfree((void **)&p->argv);
	}
	if (p->ownenv && (av = p->envv))
	{
		while (*av)
			free(*av++);
		ft_pfree((void **)&p->envv);
	}
	sh_redirectclose(&p->redirs);
	ft_vecdtor((t_vec *)&p->redirs, NULL);
	p->kind == PROC_SH ? ft_deqdtor(&p->u.sh.toks, NULL) : 0;
	p->kind == PROC_EXE ? ft_pfree((void **)&p->u.exe) : 0;
	p->kind == PROC_ERR && p->u.err.msg ? ft_pfree((void **)&p->u.err.msg) : 0;
	p->kind == PROC_ERR && p->u.err.ln ? ft_pfree((void **)&p->u.err.ln) : 0;
}

static inline pid_t	prepare(t_proc *prc, pid_t pgid, int *io, int fg)
{
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
	if (prc->child && g_sh->interact)
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
	return (YEP);
}

int					sh_proclaunch(t_proc *proc, pid_t pgid, int *io, int fg)
{
	if ((prepare(proc, pgid, io, fg)))
		return (NOP);
	if (proc->kind == PROC_SH)
		return (sh_procshlaunch(proc));
	else if (proc->kind == PROC_FN)
		return (sh_procfnlaunch(proc));
	else if (proc->kind == PROC_ERR)
		return (sh_procerrlaunch(proc));
	else if (proc->kind == PROC_BOOL)
		return (sh_procbitlaunch(proc));
	else if (proc->kind == PROC_EXE)
		return (sh_procexelaunch(proc));
	return (YEP);
}

inline int			sh_procmark(t_proc *proc, int status)
{
	if (WIFSTOPPED(status))
	{
		proc->state = PROC_STOPPED;
		proc->status = 0;
	}
	else
	{
		proc->state = PROC_COMPLETED;
		if (WIFEXITED(status))
			proc->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && WTERMSIG(status) != SIGINT)
		{
			if (WTERMSIG(status) != SIGPIPE)
				sh_err("%d: Terminated by signal %d.\n",
					(int)proc->pid, WTERMSIG(status));
			proc->status = 1;
		}
		else if (WTERMSIG(status) == SIGINT && (proc->status = 130))
			ft_putc(STDIN_FILENO, '\n');
		else
			proc->status = status;
	}
	return (YEP);
}
