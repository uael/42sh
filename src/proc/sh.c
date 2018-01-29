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

#include "ush/eval.h"

inline void		sh_procsh(t_proc *proc)
{
	sh_procctor(proc);
	ft_deqctor(&proc->u.sh.toks, sizeof(t_tok));
	proc->kind = PROC_SH;
}

inline int		sh_procshlaunch(t_proc *proc, pid_t pid)
{
	char *ln;

	g_shinteract = 0;
	g_shpgid = pid;
	ln = NULL;
	g_shstatus = sh_eval(-1, &proc->u.sh.toks, &ln);
	proc->status = g_shstatus;
	exit(g_shstatus);
}
