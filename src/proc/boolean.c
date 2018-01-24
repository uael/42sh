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

inline void		sh_procbool(t_proc *proc, t_bool boolean)
{
	ft_memset(proc, 0, sizeof(t_proc));
	proc->kind = PROC_BOOL;
	proc->u.boolean = boolean;
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, STD_FILENOS, 3 * sizeof(int));
}

inline int		sh_procboollaunch(t_proc *proc)
{
	proc->status = proc->u.boolean;
	if (proc->child)
		exit(proc->status);
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
