/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalcmd(t_proc *proc, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	int		st;

	st = NOP;
	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	if (TOK_ISCMDM(tok->id) &&
		!(st = sh_evalsimple(proc, fd, toks, ln)))
		return (YEP);
	else if (tok->id == '(' && !(st = sh_evalcompound(proc, fd, toks, ln)))
	{
		while ((tok = sh_tokpeek(toks)))
			if (TOK_ISREDIR(tok->id))
			{
				if ((st = sh_evalredir(proc, toks, ln)))
					return (st);
			}
			else
				return (YEP);
	}
	return (st);
}
