/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:39:49 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

static inline t_st	msh_eval_word(t_msh *self, t_tok *tok)
{
	t_vstr		av;
	t_st		st;
	t_dstr		*ident;
	t_cmd		bi;

	if ((bi = msh_bi(ft_tok_ident(tok)->buf)))
	{
		if (ISE(st = msh_exe_av(self, &av, ft_tok_ident(tok)->buf)))
			return (st);
		return (ft_dtor(self->st = (*bi)(self, &av),
			(t_dtor)ft_vstr_dtor, &av, NULL));
	}
	ident = ft_tok_ident(tok);
	if (ISE(st = msh_exe_av(self, &av, ident->buf)))
		return (st);
	st = msh_exe_run(self, &av);
	ft_vstr_dtor(&av, NULL);
	return (st);
}

inline t_st			msh_eval(t_msh *self, t_tok *tok)
{
	if (tok->id == MSH_TOK_WORD)
		return (msh_eval_word(self, tok));
	return (ft_ret(NOK, "%s: Unexpected token '%c'\n", "msh", tok->id));
}
