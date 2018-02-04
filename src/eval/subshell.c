/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalsubshell(t_job *job, int fd, t_deq *toks, char **ln)
{
	int		stack;
	t_proc	proc;
	t_tok	*tok;

	(void)fd;
	sh_procsh(&proc);
	stack = 0;
	while ((tok = sh_toknext(toks))->id != ')' || stack)
	{
		if (tok->id == '(')
			++stack;
		else if (tok->id == ')')
			--stack;
		*(t_tok *)ft_deqpush(&proc.u.sh.toks) = *tok;
		tok->val = NULL;
	}
	if (!proc.u.sh.toks.len)
		return (sh_evalerr(*ln, sh_tokpeek(toks), "Empty subshell"));
	sh_toknext(toks);
	(*(t_tok *)ft_deqpush(&proc.u.sh.toks)).id = TOK_END;
	*(t_proc *)ft_vecpush((t_vec *)&job->procs) = proc;
	return (YEP);
}
