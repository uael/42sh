/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 16:31:30 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

static inline t_st	sh_eval_job(t_sh *self, t_job *job, t_tok *tok)
{
	t_vstr		av;
	t_st		st;
	t_dstr		*ident;
	t_job_fn	bi;

	if (!tok || tok->id != SH_TOK_WORD)
		return (NOK);
	ident = ft_tok_ident(tok);
	if (ISE(st = sh_exe_av(self, &av, ident->buf)))
		return (st);
	if ((bi = sh_bi(ft_tok_ident(tok)->buf)))
		ft_job_fn(job, bi, av.buf, self->env.buf);
	else if (ISE(st = ft_job_exe(job, "PATH", av.buf, self->env.buf)))
		return (ft_retf(NOK, "%s: %e\n", av.buf[0], ST_TOENO(st)));
	else if (ST_NOK(st))
		return (ft_retf(NOK, "%s: Command not found\n", av.buf[0]));
	return (OK);
}

inline t_st			sh_eval(t_sh *self, t_tok *tok)
{
	t_job		job;
	t_job_op	op;

	while (sh_eval_job(self, &job, tok))
	{
		op = JOB_OP_NONE;
		if ((tok = sh_peek(self)))
		{
			if (tok->id == SH_TOK_PIPE)
				op = JOB_OP_PIPE;
		}
		if (!ft_worker_push(&self->worker, &job, op))
			return (ENO);
	}
	if (ft_vec_size(&self->worker))
		return (ft_worker_run(&self->worker, self));
	return (NOK);
}
