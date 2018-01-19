/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalsimple(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	int		st;

	st = NOP;
	if ((tok = sh_tokpeek(toks))->id == TOK_WORD)
	{
		if (ft_strchr(tok->val, '='))
			st = sh_evalassign(toks);
		else if ((st = sh_evalargv(job, fd, toks, ln)))
			return (NOP);
	}
	while ((tok = sh_tokpeek(toks)))
		if (TOK_ISREDIR(tok->id))
		{
			if ((st = sh_evalredir(job, fd, toks, ln)))
				return (NOP);
		}
		else
			return (st);
	return (st);
}
