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

inline int		sh_evalcmd(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;

	if (!(tok = sh_tokpeek(toks)))
		return (sh_synerr(*ln, NULL, "Unexpected token `%s'",
			sh_tokstr(NULL)));
	if ((tok->id == TOK_WORD || TOK_ISREDIR(tok->id)) &&
		!sh_evalsimple(job, fd, toks, ln))
		return (YEP);
	return (NOP);
}
