/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 16:02:50 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/reduce.h"

inline int	sh_reduce(t_sh *self)
{
	t_tok	*tok;
	ssize_t	st;

	if ((st = ft_lexer_until(&self->lexer, '\n')) <= 0)
		return (st < 0 ? WUT : NOP);
	tok = (t_tok *)ft_deq_begin(&self->lexer.toks) - 1;
	while (++tok != ft_deq_end(&self->lexer.toks))
		if (tok->id == SH_TOK_HEREDOC || tok->id == SH_TOK_HEREDOCT)
		{
			if (sh_reduce_heredoc(self, tok))
				return (WUT);
		}
	return (YEP);
}
