/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/andor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static inline int	pipelineerr(int st, t_tok *tok, t_bool bang, char *ln)
{
	if (st == NOP && bang)
		return (sh_evalerr(ln, tok, "Unexpected bang `%s' for empty "
			"pipeline", sh_tokstr(tok)));
	return (st);
}

inline int			sh_evalandor(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_job	right;
	int		st;

	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	if (tok->id == TOK_NOT)
	{
		job->bang = 1;
		sh_toknext(toks);
	}
	if ((st = sh_evalpipeline(job, fd, toks, ln)))
		return (pipelineerr(st, tok, job->bang, *ln));
	while (1)
		if (!(tok = sh_tokpeek(toks)))
			return (NOP);
		else if (tok->id == TOK_LAND)
		{
			while ((tok = sh_toknext(toks)))
				if (tok->id != TOK_EOL)
					break ;
			sh_jobctor(&right);
			if (!(tok = sh_tokpeek(toks)))
				return (sh_evalerr(*ln, tok, "Expected <pipeline> got `%s'",
					sh_tokstr(tok)));
			if (tok->id == TOK_NOT)
			{
				right.bang = 1;
				sh_toknext(toks);
			}
			if ((st = sh_evalpipeline(&right, fd, toks, ln)))
				return (pipelineerr(st, tok, right.bang, *ln));
			job->andor = ANDOR_AND;
			job->next = ft_memdup(&right, sizeof(t_job));
			job = job->next;
		}
		else if (tok->id == TOK_LOR)
		{
			while ((tok = sh_toknext(toks)))
				if (tok->id != TOK_EOL)
					break ;
			sh_jobctor(&right);
			if (!(tok = sh_tokpeek(toks)))
				return (sh_evalerr(*ln, tok, "Expected <pipeline> got `%s'",
					sh_tokstr(tok)));
			if (tok->id == TOK_NOT)
			{
				right.bang = 1;
				sh_toknext(toks);
			}
			if ((st = sh_evalpipeline(&right, fd, toks, ln)))
				return (pipelineerr(st, tok, right.bang, *ln));
			job->andor = ANDOR_OR;
			job->next = ft_memdup(&right, sizeof(t_job));
			job = job->next;
		}
		else
			return (YEP);
}
