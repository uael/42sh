/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/proc.h"

inline int		sh_procfork(t_proc *p, pid_t *pgid, int *io, int fg)
{
	pid_t pid;

	pid = 0;
	p->state = PROC_RUNNING;
	if (!p->child || !(pid = fork()))
		return (sh_proclaunch(p, pgid ? *pgid : 0, io, fg));
	else if (pid < 0)
		sh_exit(THROW(WUT), NULL);
	else
	{
		p->pid = pid;
		g_sh->ppid = pid;
		if (pgid)
		{
			setpgid(pid, *pgid);
			if (!*pgid)
				*pgid = pid;
		}
	}
	return (YEP);
}
