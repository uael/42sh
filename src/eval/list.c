/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static inline int	onsemicolon(t_job *job, int fd, t_deq *toks, char **ln)
{
	sh_toknext(toks);
	g_shstatus = job->processes.len ? sh_joblaunch(job, 1) : job->status;
	job->processes.len = 0;
	if (sh_evalandor(job, fd, toks, ln))
	{
		sh_jobdtor(job);
		return (NOP);
	}
	return (YEP);
}

static inline int	onamp(t_job *job, int fd, t_deq *toks, char **ln)
{
	if (!g_shinteract)
		return (onsemicolon(job, fd, toks, ln));
	sh_toknext(toks);
	if (job->processes.len)
		sh_poolpush(job);
	sh_jobctor(job);
	if (sh_evalandor(job, fd, toks, ln))
	{
		sh_jobdtor(job);
		return (NOP);
	}
	return (YEP);
}

static inline int	oneof(t_job *job)
{
	g_shstatus = job->processes.len ? sh_joblaunch(job, 1) : job->status;
	sh_jobdtor(job);
	return (YEP);
}

inline int			sh_evallist(int fd, t_deq *toks, char **ln)
{
	t_tok *tok;
	t_job job;

	sh_jobctor(&job);
	if (sh_evalandor(&job, fd, toks, ln))
		return (NOP);
	while (1)
		if ((tok = sh_tokpeek(toks))->id == TOK_AMP)
		{
			if (onamp(&job, fd, toks, ln))
				return (YEP);
		}
		else if (tok->id == TOK_SEMICOLON)
		{
			if (onsemicolon(&job, fd, toks, ln))
				return (YEP);
		}
		else if (tok->id == TOK_END || tok->id == TOK_EOL)
			return (oneof(&job));
		else
		{
			sh_jobdtor(&job);
			return (YEP);
		}
}
