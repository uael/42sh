/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 19:06:49 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline void		sh_lex(t_lexer *self)
{
	t_lrule *it;

	it = ft_vec_pushn(&self->rules, 2);
	*it = sh_tok_word;
	*(it + 1) = sh_tok_syntax;
}

inline t_tok	*sh_peek(t_sh *self)
{
	t_tok	*tok;

	if (ft_lexer_peek(&self->lexer, 0, &tok))
		return (NULL);
	return (tok);
}

inline t_tok	*sh_next(t_sh *self, t_tok **next)
{
	t_tok	*tok;

	if (ft_lexer_next(&self->lexer, 1, &tok) <= 0)
		return (NULL);
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

inline t_tok	*sh_skip(t_sh *self, char *ids)
{
	t_tok	*tok;

	while ((tok = sh_peek(self)) && tok->id)
	{
		if (!ft_strchr(ids, tok->id))
			break ;
		sh_next(self, NULL);
	}
	return (tok);
}
