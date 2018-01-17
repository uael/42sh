/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/parse.h"

static int		parseeol(t_deq *toks, char **ln)
{
	t_tok *tok;

	while ((tok = sh_tokpeek(toks)))
		if (tok->id == TOK_EOL)
			ft_deqsht(toks, NULL);
		else if (tok->id == TOK_END)
			return (YEP);
		else
			return (sh_synerr(*ln, *ln + tok->pos, "Unexpected token `%s'",
				sh_tokidstr(tok->id)));
	return (YEP);
}

inline int		sh_parse(int fd, t_deq *toks, char **ln)
{
	t_job	*job;
	t_tok	*tok;

	if (!(job = sh_parselist(fd, toks, ln)))
		return (NOP);
	if (!(tok = sh_tokpeek(toks)))
		return (YEP);
	if (tok->id == TOK_SEMICOLON)
		sh_toknext(toks);
	else if (tok->id == TOK_AMP)
	{
		sh_toknext(toks);
		job->bg = 1;
	}
	else if (tok->id == TOK_END)
		return (YEP);
	else if (tok->id != TOK_EOL)
		return (sh_synerr(*ln, *ln + tok->pos, "Unexpected token `%s'",
			sh_tokidstr(tok->id)));
	return (parseeol(toks, ln));
}
