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

#include "../ps.h"

inline int		ps_procfork(t_proc *p, pid_t *pgid, int *io, int fg)
{
	pid_t pid;

	pid = 0;
	p->state = PROC_RUNNING;
	if (!p->child || !(pid = fork()))
		return (ps_proclaunch(p, pgid ? *pgid : 0, io, fg));
	else if (pid < 0)
		g_fatalcb(THROW(WUT), NULL);
	else
	{
		p->pid = pid;
		g_pid = pid;
		if (pgid)
		{
			setpgid(pid, *pgid);
			if (!*pgid)
				*pgid = pid;
		}
	}
	return (YEP);
}
