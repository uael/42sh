/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/boolean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/proc.h"

inline void		sh_procbit(t_proc *proc, t_bool bit)
{
	sh_procctor(proc);
	proc->kind = PROC_BOOL;
	proc->u.bit = bit;
}

inline int		sh_procbitlaunch(t_proc *proc)
{
	proc->status = proc->u.bit;
	if (proc->child)
	{
		sh_procdtor(proc);
		exit(proc->status);
	}
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
