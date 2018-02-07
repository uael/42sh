/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ps.h"

inline t_procerr	*ps_procerr(t_proc *proc, char *msg, char *ln, size_t pos)
{
	if (proc->kind != PROC_ERR && proc->kind != PROC_NONE)
	{
		ps_procdtor(proc);
		ps_procctor(proc);
	}
	proc->kind = PROC_ERR;
	if (ln ? (proc->u.err.ln = ft_strdup(ln)) : 0)
		proc->u.err.pos = pos;
	msg ? (proc->u.err.msg = ft_strdup(msg)) : 0;
	proc->u.err.st = EXIT_FAILURE;
	return (&proc->u.err);
}

inline int			ps_procerrlaunch(t_proc *proc)
{
	if (proc->u.err.msg)
		ft_putf(STDERR_FILENO, proc->u.err.msg);
	if (proc->child)
	{
		ps_procdtor(proc);
		g_fatalcb(proc->u.err.st, NULL);
	}
	proc->status = proc->u.err.st;
	proc->state = PROC_COMPLETED;
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
