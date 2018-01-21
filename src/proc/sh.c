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
#include "ush/proc.h"
#include "ush/tok.h"

inline int		sh_procsh(t_proc *proc, t_deq *toks, char *ln)
{
	int		stack;
	t_tok	*tok;

	ft_memset(proc, stack = 0, sizeof(t_proc));
	ft_deqctor(&proc->u.sh.toks, sizeof(t_tok));
	proc->u.sh.ln = ln;
	if (toks)
	{
		while ((tok = sh_toknext(toks))->id != ')' && !stack)
		{
			if (tok->id == '(')
				++stack;
			else if (tok->id == ')')
				--stack;
			*(t_tok *)ft_deqpush(&proc->u.sh.toks) = *tok;
		}
		if (!proc->u.sh.toks.len)
			return (NOP);
		(*(t_tok *)ft_deqpush(&proc->u.sh.toks)).id = TOK_END;
	}
	proc->kind = PROC_SH;
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, STD_FILENOS, 3 * sizeof(int));
	return (YEP);
}

inline int		sh_procshlaunch(t_proc *proc, pid_t pid)
{
	g_shinteract = 0;
	g_shpgid = pid;
	sh_eval(-1, &proc->u.sh.toks, &proc->u.sh.ln);
	proc->status = g_shstatus;
	exit(g_shstatus);
}
