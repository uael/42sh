/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/18 17:39:57 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/ft_glob.h"

#include "ps.h"

static int			(*g_procs[6])(t_proc *proc) =
{
	[PROC_EXE] = ps_procexelaunch,
	[PROC_BI] = ps_procbilaunch,
	[PROC_FN] = ps_procfnlaunch,
	[PROC_ERR] = ps_procerrlaunch,
	[PROC_BIT] = ps_procbitlaunch
};

inline void			ps_procctor(t_proc *proc)
{
	ft_memset(proc, 0, sizeof(t_proc));
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, STD_FILENOS, 3 * sizeof(int));
}

inline void			ps_procdtor(t_proc *p)
{
	char	**av;

	DUMMY_GLOBDTOR(&p->argv);
	if (p->ownenv && (av = p->envv))
	{
		while (*av)
			free(*av++);
		ft_pfree((void **)&p->envv);
	}
	ps_redirectclose(&p->redirs);
	ft_vecdtor((t_vec *)&p->redirs, NULL);
	p->kind == PROC_FN && p->u.fn.dtor ? p->u.fn.dtor(p->u.fn.data) : 0;
	p->kind == PROC_ERR && p->u.err.msg ? ft_pfree((void **)&p->u.err.msg) : 0;
	p->kind == PROC_ERR && p->u.err.ln ? ft_pfree((void **)&p->u.err.ln) : 0;
}

static inline int	prepare(t_proc *prc, pid_t pgid, int *io, int fg)
{
	prc->close != STDIN_FILENO && prc->close != io[0] ? close(prc->close) : 0;
	if (ft_dup2std(io, prc->src) ||
		ps_redirect(&prc->redirs, prc->child ? NULL : prc->scope))
	{
		prc->child ? 0 : ft_dup2std(prc->scope, STD_FILENOS);
		if (prc->child)
			g_fatalcb(EXIT_FAILURE, NULL);
		prc->status = EXIT_FAILURE;
		return (WUT);
	}
	if (prc->child && g_tty)
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

int					ps_proclaunch(t_proc *proc, pid_t pgid, int *io, int fg)
{
	if ((prepare(proc, pgid, io, fg)))
		return (NOP);
	if (proc->child && g_tty)
		g_tty = 0;
	return (proc->kind == 0 ? YEP : g_procs[proc->kind](proc));
}

inline int			ps_procmark(t_proc *proc, int status)
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
				g_errcb("%d: Terminated by signal %d.\n",
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
