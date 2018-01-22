/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/argv.c                                        :+:      :+:    :+:   */
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
	int		st;

	if ((st = sh_evalcmd(job, fd, toks, ln)))
		return (st);
	while (1)
		if (!(tok = sh_tokpeek(toks)))
			return (NOP);
		else if (tok->id == TOK_PIPE)
		{
			while ((eol = sh_toknext(toks)))
				if (eol->id != TOK_EOL)
					break ;
			if ((st = sh_evalcmd(job, fd, toks, ln)))
			{
				tok = sh_tokpeek(toks);
				return (st == NOP ? sh_evalerr(*ln, tok, "Unexpected token `%s'"
					" on pipeline sequence", sh_tokstr(tok)) : st);
			}
		}
		else
			return (YEP);
}
