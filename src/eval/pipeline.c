/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalpipeline(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_tok	*eol;

	if (sh_evalcommand(job, fd, toks, ln))
		return (NOP);
	while (1)
		if ((tok = sh_tokpeek(toks))->id == TOK_PIPE)
		{
			while ((eol = sh_toknext(toks)))
				if (eol->id != TOK_EOL)
					break ;
			if (sh_evalcommand(job, fd, toks, ln))
				return (sh_parseerr(*ln, tok, "Unfinished pipeline sequence "
					"near `%s'", sh_tokstr(tok)));
		}
		else
			return (YEP);
}
