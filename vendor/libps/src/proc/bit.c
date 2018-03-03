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

#include "../ps.h"

inline void		ps_procbit(t_proc *proc, t_bool bit)
{
	proc->kind = PROC_BIT;
	proc->u.bit = bit;
}

inline int		ps_procbitlaunch(t_proc *proc)
{
	return (proc->status = proc->u.bit);
}
