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

inline int		sh_evallist(int fd, t_deq *toks, char **ln)
{
	t_tok *tok;
	t_job job;

	sh_jobctor(&job);
	if (sh_evalandor(&job, fd, toks, ln))
		return (NOP);
	while (1)
		if ((tok = sh_tokpeek(toks))->id == TOK_AMP)
		{
			sh_toknext(toks);
			sh_poolpush(&job);
			sh_jobctor(&job);
			if (sh_evalandor(&job, fd, toks, ln))
				return (YEP);
		}
		else if (tok->id == TOK_SEMICOLON)
		{
			sh_toknext(toks);
			sh_joblaunch(&job, 1);
			g_shstatus = job.processes.len ?
				job.processes.buf[job.processes.len - 1].status : 0;
			job.processes.len = 0;
			if (sh_evalandor(&job, fd, toks, ln))
				return (YEP);
		}
		else
		{
			sh_joblaunch(&job, 1);
			g_shstatus = job.processes.len ?
				job.processes.buf[job.processes.len - 1].status : 0;
			sh_jobdtor(&job);
			return (YEP);
		}
}
