/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalredir(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok *tok;

	(void)fd;
	tok = sh_tokpeek(toks);
	if (!job->processes.len)
		return (sh_parseerr(*ln, tok, "Unexpected redirection `%s' "
			"for empty command line", sh_tokstr(tok)));
	if (tok->id == '<')
		return (sh_evalrin(job, fd, toks, ln));
	if (tok->id == '>')
		return (sh_evalrout(job, fd, toks, ln));
	return (NOP);
}
