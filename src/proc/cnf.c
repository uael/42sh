/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/cnf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/proc.h"

inline int		sh_proccnflaunch(t_proc *proc)
{
	char *msg;

	msg = proc->u.cnf.st == PROC_NORIGHTS ? "%s: permission denied" :
		"%s: Command not found";
	if (proc->u.cnf.ln)
		sh_synerr(proc->u.cnf.ln, proc->u.cnf.it, msg, proc->u.cnf.exe);
	else
		ft_putf(STDERR_FILENO, msg, proc->u.cnf.exe);
	exit(proc->u.cnf.st);
}
