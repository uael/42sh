/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:48:27 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline t_st	sh_eval_exe(t_sh *self, t_job **pjob, t_tok *tok)
{
	t_vstr		av;
	t_st		st;
	t_job		job;
	t_job		hdoc;

	if (tok->id != SH_TOK_WORD)
		return (SH_NEXT);
	if (ISE(st = sh_exe_av(self, &av, ft_tok_ident(tok)->buf)))
		return (st);
	if (ISE(st = ft_job_exe(&job, "PATH", av.buf, self->env.buf)))
		return (ft_retf(SH_NOK, N_SH"%s: %e\n", av.buf[0], ST_TOENO(st)));
	else if (ST_NOK(st))
		return (ft_retf(SH_NOK, N_SH"%s: Command not found\n", av.buf[0]));
	if ((tok = sh_skip(self, "\t ")) && tok->id == SH_TOK_HEREDOC)
	{
		sh_next(self, NULL);
		ft_job_output(&hdoc, ft_tok_ident(tok)->buf);
		if (!(*pjob = ft_worker_push(&self->worker, &hdoc)))
			return (ENO);
		ft_job_pipe(*pjob);
	}
	ft_job_data(&job, self);
	return ((*pjob = ft_worker_push(&self->worker, &job)) ? SH_OK : ENO);
}
