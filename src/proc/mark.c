/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
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
	if (WIFSTOPPED(status))
	{
		proc->state = PROC_STOPPED;
		proc->status = 0;
	}
	else
	{
		proc->state = PROC_COMPLETED;
		if (WIFEXITED(status))
			proc->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && WTERMSIG(status) != 2)
		{
			if (WTERMSIG(status) != SIGPIPE)
				sh_err("%d: Terminated by signal %d.\n",
					(int)proc->pid, WTERMSIG(status));
			proc->status = 1;
		}
		else if (WTERMSIG(status) == 2)
		{
			ft_putc(STDIN_FILENO, '\n');
			proc->status = 130;
		}
		else
			proc->status = status;
	}
	return (YEP);
}
