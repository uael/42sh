/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:05:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline t_st	sh_eval_heredoc(t_sh *self, t_job **pjob, t_tok *tok)
{
	t_job	job;

	if (tok->id != SH_TOK_HEREDOC)
		return (SH_NEXT);
	ft_job_output(&job, ft_tok_ident(tok)->buf);
	return ((*pjob = ft_worker_push(&self->worker, &job)) ? SH_OK : ENO);
}
