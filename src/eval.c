/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 16:16:29 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

static t_st	(*g_rules[])(t_sh *self, t_job **pjob, t_tok *tok) =
{
	sh_eval_sep,
	sh_eval_pipe,
	sh_eval_rin,
	sh_eval_rout,
	sh_eval_heredoc,
	sh_eval_bi,
	sh_eval_exe,
	NULL
};

inline t_st	sh_eval(t_sh *self)
{
	t_tok		*tok;
	t_st		st;
	t_job		*job;
	t_st		(**rule)(t_sh *, t_job **, t_tok *);

	if (ST_NOK(st = sh_reduce(self)))
		return (st);
	job = NULL;
	while ((rule = g_rules - 1))
		if (!(tok = sh_next(self, NULL)))
			return (NOK);
		else
		{
			while (*++rule)
				if (ISE(st = (*rule)(self, &job, tok)))
					return (st);
				else if (st == SH_NEXT)
					continue ;
				else if (st == SH_OK || st == SH_NOK)
					break ;
				else if (st == SH_BREAK)
					return (OK);
				else if (st == SH_BREAK_NOK && sh_peek(self) == tok)
				{
					sh_consume_line(self);
					sh_clean(self);
					return (self->st = NOK);
				}
		}
	ft_putf(1, "-- wut --\n");
	return (NOK);
}
