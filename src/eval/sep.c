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
#include "msh/sig.h"

static int			g_st;

static void			worker_sigint_hdl(int sign)
{
	(void)sign;
	ft_putc(1, '\n');
	ft_putc(0, '\n');
	g_st = 130;
}

inline int	sh_eval_sep(t_sh *self, t_job **job, t_tok *tok)
{
	char	id;

	id = tok->id;
	if (!ft_strchr(";\n", id))
		return (SH_NEXT);
	if (ft_vec_size(&self->worker))
	{
		g_st = 0;
		signal(SIGINT,  worker_sigint_hdl);
		ft_worker_run(&self->worker);
		self->st = ft_worker_join(&self->worker);
		if (g_st)
			self->st = g_st;
		signal(SIGINT, sh_sigint_hdl);
	}
	else if (id == ';')
	{
		ft_putf(2, N_SH" '%c'\n", id);
		self->st = NOP;
	}
	sh_clean(self);
	if (id == '\n')
		return (SH_BREAK);
	*job = NULL;
	return (SH_OK);
}
