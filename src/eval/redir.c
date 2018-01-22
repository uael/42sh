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

#define UNEXPTD "Unexpected redirection `%s' for empty command line"

inline int		sh_evalredir(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;

	(void)fd;
	tok = sh_tokpeek(toks);
	if (!job->processes.len)
		return (sh_evalerr(*ln, tok, UNEXPTD, sh_tokstr(tok)));
	if (tok->id == '<')
		return (sh_evalrin(job, fd, toks, ln));
	if (tok->id == '>' || tok->id == TOK_RPOUT)
		return (sh_evalrout(job, fd, toks, ln));
	if (tok->id == TOK_CMP)
		return (sh_evalcmp(job, fd, toks, ln));
	if (tok->id == TOK_RAOUT)
		return (sh_evalraout(job, fd, toks, ln));
	if (tok->id == TOK_HEREDOC || tok->id == TOK_HEREDOCT)
		return (sh_evalheredoc(job, fd, toks, ln));
	if (tok->id == TOK_LAMP)
		return (sh_evallamp(job, fd, toks, ln));
	if (tok->id == TOK_RAMP)
		return (sh_evalramp(job, fd, toks, ln));
	return (NOP);
}
