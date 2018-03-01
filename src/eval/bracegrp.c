/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bracegrp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int			sh_evalbracegrp(t_proc *prc, int fd, t_deq *toks, char **ln)
{
	t_tok		*tok;

	(void)fd;
	(void)prc;
	sh_toknext(toks);
	while (1)
	{
		while ((tok = sh_tokpeek(toks)) && tok->id == '\n')
			sh_toknext(toks);
		sh_evallist(fd, toks, ln) ? 0 : (g_sh->status = 1);
		while ((tok = sh_tokpeek(toks)) && tok->id == '\n')
			sh_toknext(toks);
		if (!(tok = sh_tokpeek(toks)))
			return (NOP);
		if (tok->id == '}')
			break ;
	}
	sh_toknext(toks);
	return (YEP);
}
