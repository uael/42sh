/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/proc.h"

inline void		sh_procerr(t_proc *proc, char *msg, t_tok *tok, char *ln)
{
	if (proc->kind != PROC_ERR && proc->kind != PROC_NONE)
		sh_procdtor(proc);
	ft_memset(proc, 0, sizeof(t_proc));
	proc->kind = PROC_ERR;
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, STD_FILENOS, 3 * sizeof(int));
	if ((proc->u.err.ln = ln) && tok)
		proc->u.err.it = ln + tok->pos;
	proc->u.err.msg = msg;
	proc->u.err.st = EXIT_FAILURE;
}

inline int		sh_procerrlaunch(t_proc *proc)
{
	if (proc->u.err.ln)
		sh_synerr(proc->u.err.ln, proc->u.err.it, proc->u.err.msg);
	else
		ft_putf(STDERR_FILENO, proc->u.err.msg);
	if (proc->child)
		exit(proc->u.err.st);
	proc->status = proc->u.err.st;
	proc->state = PROC_COMPLETED;
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
