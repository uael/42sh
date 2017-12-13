/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/rout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:05:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline int	sh_eval_rout(t_sh *self, t_job **job, t_tok *t)
{
	if (t->id != SH_TOK_ROUT)
		return (SH_NEXT);
	if (!*job)
		return (ft_retf(SH_BREAK_NOK, N_SH"oops '%c'\n", t->id));
	if (!(t = sh_peek(self)) || t->id != SH_TOK_WORD)
		return (t ? ft_retf(SH_BREAK_NOK, N_SH"o '%c'\n", t->id) : (int)SH_OK);
	sh_next(self, NULL);
	if (((*job)->out = open(ft_tok_ident(t)->buf, O_RDWR | O_CREAT,
		S_IRUSR | S_IWUSR)) < 0)
		return (THROW(SH_BREAK_NOK));
	return (SH_OK);
}
