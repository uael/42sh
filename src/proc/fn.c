/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/proc.h"

static int		exhdl(int rcode, void *arg)
{
	(void)arg;
	errno = 0;
	return (rcode);
}

inline void		sh_procfn(t_proc *proc, t_procfn *fn, char **envv)
{
	sh_procctor(proc);
	proc->envv = envv;
	proc->u.fn = fn;
	proc->kind = PROC_FN;
}

inline int		sh_procfnlaunch(t_proc *proc)
{
	t_ex_hdl	dfl;
	char		**av;

	av = proc->argv;
	while (*av)
		++av;
	ft_exbind(EXALL, ft_exhdl(exhdl, NULL), &dfl);
	proc->status = proc->u.fn((int)(av - proc->argv), proc->argv, proc->envv);
	ft_exbind(EXALL, dfl, NULL);
	if (proc->child)
	{
		sh_procdtor(proc);
		sh_exit(proc->status, NULL);
	}
	proc->state = PROC_COMPLETED;
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
