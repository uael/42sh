/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalcompound(t_proc *proc, int fd, t_deq *toks, char **ln)
{
	t_tok *tok;

	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	if (tok->id == '(')
		return (sh_evalsubshell(proc, fd, toks, ln));
	if (tok->id == '{')
		return (sh_evalbracegrp(proc, fd, toks, ln));
	else if (tok->id == TOK_IF)
		return (sh_evalifclause(proc, fd, toks, ln));
	else if (tok->id == TOK_WHILE)
		return (sh_evalwhileclause(proc, toks, ln));
	return (NOP);
}
