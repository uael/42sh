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
	ft_memset(proc, 0, sizeof(t_proc));
	proc->envv = envv;
	proc->u.fn = fn;
	proc->kind = PROC_FN;
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, STD_FILENOS, 3 * sizeof(int));
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
		exit(proc->status);
	proc->state = PROC_COMPLETED;
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
