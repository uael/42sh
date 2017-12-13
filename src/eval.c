/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 11:58:44 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

static int			(*g_rules[])(t_sh *self, t_job **pjob, t_tok *tok) =
{
	sh_eval_sep,
	sh_eval_pipe,
	sh_eval_rin,
	sh_eval_rout,
	sh_eval_raout,
	sh_eval_heredoc,
	sh_eval_bi,
	sh_eval_exe,
	NULL
};

static inline int	eval_rules(t_sh *self, t_tok *tok, t_job **job)
{
	int		st;
	int		(**rule)(t_sh *, t_job **, t_tok *);

	rule = g_rules - 1;
	while (*++rule)
		if ((st = (*rule)(self, job, tok)) < 0)
			return (NOP);
		else if (st == SH_NEXT)
			continue ;
		else if (st == SH_OK || st == SH_NOK)
			break ;
		else if (st == SH_BREAK)
			return (YEP);
		else if (st == SH_BREAK_NOK)
		{
			sh_consume_line(self);
			sh_clean(self);
			self->st = NOP;
			return (YEP);
		}
	return (SH_NEXT);
}

inline int			sh_eval(t_sh *self)
{
	t_tok	*tok;
	int		st;
	t_job	*job;

	if (sh_reduce(self))
		return (WUT);
	job = NULL;
	while (1)
		if (!(tok = sh_next(self, NULL)))
			return (NOP);
		else if ((st = eval_rules(self, tok, &job)) != SH_NEXT)
			return (st);
}
