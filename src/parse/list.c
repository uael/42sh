/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse/list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/parse.h"

#define ANDOR "Expected <and_or> got `%s'"

inline t_job	*sh_parselist(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_job	*job;
	t_job	*next;

	if (!(job = sh_parseandor(fd, toks, ln)))
		return (NULL);
	while (1)
		if ((tok = sh_tokpeek(toks))->id == TOK_AMP)
		{
			tok = sh_toknext(toks);
			job->bg = 1;
			sh_joblaunch(job, 0);
			if (!(next = sh_parseandor(fd, toks, ln)))
				return (sh_parseerr(*ln, tok, ANDOR, sh_tokidstr(tok->id)));
			job = next;
		}
		else if (tok->id == TOK_SEMICOLON)
		{
			tok = sh_toknext(toks);
			sh_joblaunch(job, 1);
			if (!(next = sh_parseandor(fd, toks, ln)))
				return (sh_parseerr(*ln, tok, ANDOR, sh_tokidstr(tok->id)));
			job = next;
		}
		else
		{
			sh_joblaunch(job, 1);
			return (job);
		}
}
