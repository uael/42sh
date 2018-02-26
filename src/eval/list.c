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
	int		st;
	t_tok	*tok;

	if (!job->procs.len)
		return (NOP);
	sh_toknext(toks);
	if (job->procs.len)
	{
		g_sh->status = ps_joblaunch(job, 1);
		ps_jobctor(job);
	}
	tok = sh_tokpeek(toks);
	if ((st = sh_evalandor(job, fd, toks, ln)))
	{
		ps_jobdtor(job);
		return (st == OUF || tok != sh_tokpeek(toks) ? st : YEP);
	}
	return (YEP);
}

static inline int	onamp(t_job *job, int fd, t_deq *toks, char **ln)
{
	int		st;
	t_tok	*tok;

	if (!job->procs.len)
		return (NOP);
	sh_toknext(toks);
	if (job->procs.len)
	{
		g_sh->status = ps_joblaunch(ps_poolpush(job), 0);
		ps_jobctor(job);
	}
	tok = sh_tokpeek(toks);
	if ((st = sh_evalandor(job, fd, toks, ln)))
	{
		ps_jobdtor(job);
		return (st == OUF || tok != sh_tokpeek(toks) ? st : YEP);
	}
	return (YEP);
}

static inline int	oneof(t_job *job)
{
	if (job->procs.len)
	{
		g_sh->status = ps_joblaunch(job, 1);
		ps_jobctor(job);
	}
	return (YEP);
}

inline int			sh_evallist(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_job	job;
	int		st;

	ps_jobctor(&job);
	if (sh_evalandor(&job, fd, toks, ln) == OUF)
		return (ft_dtor(OUF, (t_dtor)ps_jobdtor, &job, NULL));
	while (1)
		if (!(tok = sh_tokpeek(toks)))
			return (ft_dtor(YEP, (t_dtor)ps_jobdtor, &job, NULL));
		else if (tok->id == TOK_AMP)
		{
			if ((st = onamp(&job, fd, toks, ln)))
				return (ft_dtor(st, (t_dtor)ps_jobdtor, &job, NULL));
		}
		else if (tok->id == TOK_SEMICOLON)
		{
			if ((st = onsemicolon(&job, fd, toks, ln)))
				return (ft_dtor(st, (t_dtor)ps_jobdtor, &job, NULL));
		}
		else if (tok->id == TOK_END || tok->id == TOK_EOL)
			return (ft_dtor(oneof(&job), (t_dtor)ps_jobdtor, &job, NULL));
		else
			return (ft_dtor(NOP, (t_dtor)ps_jobdtor, &job, NULL));
}
