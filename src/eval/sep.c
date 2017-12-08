/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 16:13:26 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline t_st	sh_eval_sep(t_sh *self, t_job **job, t_tok *tok)
{
	t_st	st;
	char	id;

	id = tok->id;
	if (ft_strchr(";\n", id))
	{
		if (ft_vec_size(&self->worker))
		{
			if (ISE(st = ft_worker_run(&self->worker)))
				ft_putf(2, N_SH"%e", ST_TOENO(st));
			self->st = ft_worker_join(&self->worker);
		}
		sh_clean(self);
		if (id == '\n')
			return (SH_BREAK);
		*job = NULL;
		return (SH_OK);
	}
	else if (ft_strchr("\t ", id))
		return (SH_OK);
	return (SH_NEXT);
}
