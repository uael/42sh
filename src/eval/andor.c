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

#define UNXPTD "syntax error: Unexpected bang `%s' for empty pipeline"
#define UEH "syntax error: Expected <pipeline> got `%s'"
#define UEP "syntax error: Missing right operand after `%s'"
#define EBANG 1 << 1
#define EINSQ 1 << 2

static inline int	pipelineerr(int st, t_tok *tok, int flags, char *ln)
{
	if (st == NOP && (flags & EBANG))
		return (sh_evalerr(ln, tok, UNXPTD, sh_tokstr(tok)));
	if (st == NOP && (flags & EINSQ))
	{
		if (tok->id == TOK_LAND || tok->id == TOK_LOR)
			return (sh_evalerr(ln, tok, UEP, sh_tokstr(tok)));
		return (sh_evalerr(ln, tok, UEH, sh_tokstr(tok)));
	}
	return (st);
}

static int			separator(t_deq *toks, t_job *right, t_tok *tok)
{
	while ((tok = sh_toknext(toks)))
		if (tok->id != TOK_EOL)
			break ;
	sh_jobctor(right);
	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	if (tok->id == TOK_NOT)
	{
		right->bang = 1;
		sh_toknext(toks);
	}
	return (YEP);
}

static t_job		*jobaddnext(t_job *right, t_job *job, t_bool m)
{
	job->andor = m ? ANDOR_AND : ANDOR_OR;
	job->next = ft_memdup(right, sizeof(t_job));
	job = job->next;
	return (job);
}

inline int			sh_evalandor(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_job	right;
	int		st;

	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	tok->id == TOK_NOT && (job->bang = 1) ? sh_toknext(toks) : 0;
	if ((st = sh_evalpipeline(job, fd, toks, ln)))
		return (pipelineerr(st, tok, job->bang ? EBANG : 0, *ln));
	while (1)
		if (!(tok = sh_tokpeek(toks)))
			return (NOP);
		else if (tok->id == TOK_LAND || tok->id == TOK_LOR)
		{
			if (separator(toks, &right, tok))
				return (sh_evalerr(*ln, tok, UEP, sh_tokstr(tok)));
			if ((st = sh_evalpipeline(&right, fd, toks, ln)))
			{
				return (pipelineerr(st, sh_tokpeek(toks),
					(right.bang ? EBANG : 0) | EINSQ, *ln));
			}
			job = jobaddnext(&right, job, (t_bool)(tok->id == TOK_LAND));
		}
		else
			return (YEP);
}
