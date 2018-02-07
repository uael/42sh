/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ps.h"

inline void		ps_procfn(t_proc *proc, t_proccb *cb, t_dtor dtor, void *data)
{
	ps_procctor(proc);
	proc->kind = PROC_FN;
	proc->u.fn.cb = cb;
	proc->u.fn.dtor = dtor;
	proc->u.fn.data = data;
}

inline int		ps_procfnlaunch(t_proc *proc)
{
	proc->status = proc->u.fn.cb(proc->u.fn.data);
	if (proc->child)
	{
		ps_procdtor(proc);
		g_fatalcb(proc->status, NULL);
	}
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
