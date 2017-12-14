/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline void		sh_lex(t_lexer *self)
{
	t_lrule *it;

	it = ft_vec_pushn(&self->rules, 4);
	*it = sh_lex_skip;
	*(it + 1) = sh_lex_op;
	*(it + 2) = sh_lex_word;
	*(it + 3) = sh_lex_syn;
}

inline t_tok	*sh_peek(t_sh *self)
{
	t_tok	*tok;

	if (ft_lexer_peek(&self->lexer, 0, &tok))
		return (NULL);
	if (tok->id == SH_TOK_SKIP)
		sh_next(self, &tok);
	return (tok);
}

inline t_tok	*sh_next(t_sh *self, t_tok **next)
{
	t_tok	*tok;

	if (ft_lexer_next(&self->lexer, 1, &tok) <= 0)
		return (NULL);
	if (tok->id == SH_TOK_SKIP)
		return (sh_next(self, next));
	if (next)
		*next = sh_peek(self);
	return (tok);
}

inline void		sh_consume_line(t_sh *self)
{
	t_tok	*tok;

	while ((tok = sh_peek(self)) && tok->id)
		if ((tok = sh_next(self, NULL)) && tok->id == '\n')
			break ;
}
