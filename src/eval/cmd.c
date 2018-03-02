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

inline int			sh_evalcmd(t_proc *proc, int fd, t_deq *toks, char **ln)
{
	t_tok	*t;
	int		st;

	if (!(t = sh_tokpeek(toks)))
		return (NOP);
	if (t->id == TOK_FUNCTION)
		return (sh_evalfuncdef(proc, fd, toks, ln));
	if (sh_tokis(t, TOKS_LEFT))
	{
		if ((st = sh_evalcompound(proc, fd, toks, ln)))
			return (st);
		while ((t = sh_tokpeek(toks)))
			if (sh_tokis(t, TOKS_REDIR))
			{
				if ((st = sh_evalredir(proc, toks, ln)))
					return (st);
			}
			else
				return (YEP);
	}
	else if (!sh_tokis(t, TOKS_RIGHT) && sh_tokis(t, TOKS_REDIR | TOKS_WORD))
		return (sh_evalsimple(proc, fd, toks, ln));
	return (NOP);
}
