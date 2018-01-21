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

#include "ush/proc.h"

inline int		sh_procshlaunch(t_proc *proc, pid_t pid)
{
	g_shinteract = 0;
	g_shpgid = pid;
	sh_eval(-1, &proc->u.sh.toks, &proc->u.sh.ln);
	proc->status = g_shstatus;
	exit(g_shstatus);
}
