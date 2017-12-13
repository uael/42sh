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

inline int	sh_eval_rin(t_sh *self, t_job **job, t_tok *t)
{
	char *word;

	if (t->id != SH_TOK_RIN)
		return (SH_NEXT);
	if (!*job)
		return (ft_retf(SH_BREAK_NOK, N_SH"oops '%c'\n", t->id));
	if (t->val && t->val->kind == TOKV_I32)
		(*job)->from = t->val->val.i32;
	else
		(*job)->from = STDIN_FILENO;
	if (!(t = sh_peek(self)) || t->id != SH_TOK_WORD)
		return (t ? ft_retf(SH_BREAK_NOK, N_SH"o '%c'\n", t->id) : (int)SH_OK);
	sh_next(self, NULL);
	word = ft_tok_ident(t)->buf;
	if (((*job)->to = open(word, O_RDWR, S_IRUSR | S_IWUSR)) < 0)
		return (ft_retf(SH_BREAK_NOK, N_SH"%s: %e\n", word, errno));
	return (SH_OK);
}
