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
	int st;

	sh_toknext(toks);
	if (job->processes.len)
	{
		sh_joblaunch(job, 1);
		sh_jobctor(job);
	}
	if ((st = sh_evalandor(job, fd, toks, ln)))
	{
		sh_jobctor(job);
		return (st);
	}
	return (YEP);
}

static inline int	onamp(t_job *job, int fd, t_deq *toks, char **ln)
{
	int st;

	if (!g_shinteract)
		return (onsemicolon(job, fd, toks, ln));
	sh_toknext(toks);
	if (job->processes.len)
	{
		sh_joblaunch(job, 0);
		sh_jobctor(job);
	}
	if ((st = sh_evalandor(job, fd, toks, ln)))
	{
		sh_jobctor(job);
		return (st);
	}
	return (YEP);
}

static inline int	oneof(t_job *job)
{
	if (job->processes.len)
	{
		sh_joblaunch(job, 1);
		sh_jobctor(job);
	}
	return (YEP);
}

inline int			sh_evallist(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_job	job;
	int		st;

	sh_jobctor(&job);
	if (sh_evalandor(&job, fd, toks, ln) == ERR)
		return (ERR);
	while (1)
		if (!(tok = sh_tokpeek(toks)))
			return (ft_dtor(YEP, (t_dtor)sh_jobdtor, &job, NULL));
		else if (tok->id == TOK_AMP)
		{
			if ((st = onamp(&job, fd, toks, ln)))
				return (st == NOP ? YEP : st);
		}
		else if (tok->id == TOK_SEMICOLON)
		{
			if ((st = onsemicolon(&job, fd, toks, ln)))
				return (st == NOP ? YEP : st);
		}
		else if (tok->id == TOK_END || tok->id == TOK_EOL)
			return (oneof(&job));
		else
			return (ft_dtor(YEP, (t_dtor)sh_jobdtor, &job, NULL));
}
