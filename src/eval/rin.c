/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/rin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:05:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline t_st	sh_eval_rin(t_sh *self, t_job **job, t_tok *tok)
{
	if (tok->id != SH_TOK_RIN)
		return (SH_NEXT);
	if (!*job)
		return (ft_retf(SH_BREAK_NOK, N_SH"Unexpected token '%c'\n", tok->id));
	if (!(tok = sh_skip(self, "\t ")) || tok->id != SH_TOK_WORD)
		return (tok ? ft_retf(SH_BREAK_NOK, N_SH"Unexpected token '%c'\n",
			tok->id) : (t_st)SH_OK);
	(*job)->in = ft_tok_ident(tok)->buf;
	sh_next(self, NULL);
	return (SH_OK);
}
