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

inline int		sh_procshlaunch(t_proc *proc)
{
	char	*ln;
	t_scope	*sh;

	sh = g_sh;
	sh_scope();
	ft_memcpy(g_sh, sh, sizeof(t_scope));
	g_sh->tty = 0;
	sh_eval(-1, &proc->u.sh.toks, &ln) ? (g_sh->status = 1) : 0;
	proc->status = g_sh->status;
	sh_unscope();
	sh_procdtor(proc);
	exit(proc->status);
}
