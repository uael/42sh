/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 12:14:15 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline int	sh_eval_exe(t_sh *self, t_job **pjob, t_tok *tok)
{
	t_vstr	av;
	int		st;
	t_job	job;
	t_job	hdoc;

	if (tok->id != SH_TOK_WORD)
		return (SH_NEXT);
	sh_exe_av(self, &av, ft_tok_ident(tok)->buf);
	if ((st = ft_job_exe(&job, "PATH", av.buf, self->env.buf)) < 0)
		return (WUT);
	else if (st)
		return (ft_retf(SH_NOK, N_SH"%s: Command not found\n", av.buf[0]));
	if ((tok = sh_skip(self, "\t ")) && tok->id == SH_TOK_HEREDOC)
	{
		sh_next(self, NULL);
		ft_job_output(&hdoc, ft_tok_ident(tok)->buf);
		*pjob = ft_worker_push(&self->worker, &hdoc);
		ft_job_pipe(*pjob);
	}
	ft_job_data(&job, self);
	*pjob = ft_worker_push(&self->worker, &job);
	return (SH_NOK);
}
