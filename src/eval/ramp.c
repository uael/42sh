/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/ramp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:06:07 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline int	sh_eval_ramp(t_sh *self, t_job **job, t_tok *t)
{
	t_dup2	dup;
	char	*word;

	(void)self;
	if (t->id != SH_TOK_RAMP)
		return (SH_NEXT);
	if (!*job)
		return (ft_retf(SH_BREAK_NOK, N_SH"Syntax error '%c'\n", t->id));
	dup.from = t->val && t->val->kind == TOKV_I32
		? t->val->val.i32 : STDOUT_FILENO;
	if (!(t = sh_peek(self)) || t->id != SH_TOK_WORD)
		return (t ? ft_retf(SH_BREAK_NOK, N_SH"Syntax error '%c'\n", t->id) : (int)SH_OK);
	sh_next(self, NULL);
	word = ft_tok_ident(t)->buf;
	if (ft_strcmp(word, "-") == 0)
		dup.to = -1;
	else if (ft_isdigit(*word) && ft_strlen(word) == 1)
		dup.to = *word - '0';
	else
		return (ft_retf(SH_BREAK_NOK, N_SH"ambiguous redirect '%c'\n", t->id));
	ft_vec_pushc(&(*job)->dups, &dup);
	return (SH_OK);
}
