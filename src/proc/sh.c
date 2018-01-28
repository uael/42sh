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

inline int		sh_procsh(t_proc *proc, t_deq *toks)
{
	int		stack;
	t_tok	*tok;

	stack = 0;
	sh_procctor(proc);
	ft_deqctor(&proc->u.sh.toks, sizeof(t_tok));
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
	return (YEP);
}

inline int		sh_procshlaunch(t_proc *proc, pid_t pid)
{
	char *ln;

	g_shinteract = 0;
	g_shpgid = pid;
	ln = NULL;
	g_shstatus = sh_eval(-1, &proc->u.sh.toks, &ln);
	proc->status = g_shstatus;
	return (sh_exit(g_shstatus, NULL));
}
