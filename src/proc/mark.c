/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/mark.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/proc.h"

inline int		sh_procmark(t_proc *proc, int status)
{
	proc->status = status;
	if (WIFEXITED(status))
		proc->status = WEXITSTATUS(status);
	if (WIFSTOPPED(status))
		proc->state = PROC_STOPPED;
	else
	{
		proc->state = PROC_COMPLETED;
		if (WIFSIGNALED(status))
			sh_err("%d: Terminated by signal %d.\n",
				(int)proc->pid, WTERMSIG(status));
	}
	return (YEP);
}
