/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/bit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../api.h"

inline void		ps_procbit(t_proc *proc, t_bool bit)
{
	ps_procctor(proc);
	proc->kind = PROC_BIT;
	proc->u.bit = bit;
}

inline int		ps_procbitlaunch(t_proc *proc)
{
	proc->status = proc->u.bit;
	if (proc->child)
	{
		ps_procdtor(proc);
		g_fatalcb(proc->status, NULL);
	}
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
