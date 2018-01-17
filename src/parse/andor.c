/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse/andor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/parse.h"

#define PIPELINE "Expected <pipeline> got `%s'"

inline t_job	*sh_parseandor(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_job	*job;
	t_job	*next;

	if (!(job = sh_parsepipeline(fd, toks, ln)))
		return (NULL);
	while (1)
		if ((tok = sh_tokpeek(toks))->id == TOK_LAND)
		{
			while ((tok = sh_toknext(toks)))
				if (tok->id != TOK_EOL)
					break ;
			job->and = 1;
			if (!(next = sh_parsepipeline(fd, toks, ln)))
				return (sh_parseerr(*ln, tok, PIPELINE, sh_tokstr(tok)));
			job = next;
		}
		else if (tok->id == TOK_LOR)
		{
			while ((tok = sh_toknext(toks)))
				if (tok->id != TOK_EOL)
					break ;
			job->or = 1;
			if (!(next = sh_parsepipeline(fd, toks, ln)))
				return (sh_parseerr(*ln, tok, PIPELINE, sh_tokstr(tok)));
			job = next;
		}
		else
			return (job);
}
