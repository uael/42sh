/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 08:03:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline t_ret	msh_lex(t_lexer *self)
{
	t_lrule *it;

	if (!(it = ft_vec_pushn(&self->rules, 2)))
		return (RET_ERR);
	*it = msh_tok_word;
	*(it + 1) = msh_tok_syntax;
	return (RET_OK);
}

inline t_tok	*msh_peek(t_msh *self)
{
	t_tok	*tok;
	t_ret	r;

	if ((r = ft_lexer_peek(&self->lexer, 0, &tok)) == RET_ERR)
		MSH_EXIT(EXIT_FAILURE, self);
	return (r == RET_OK ? tok : NULL);
}

inline t_tok	*msh_peekn(t_msh *self, size_t n)
{
	t_tok	*tok;
	t_ret	r;

	if ((r = ft_lexer_peek(&self->lexer, n, &tok)) == RET_ERR)
		MSH_EXIT(EXIT_FAILURE, self);
	return (r == RET_OK ? tok : NULL);
}

inline t_tok	*msh_next(t_msh *self, t_tok **next)
{
	t_tok	*tok;
	ssize_t	s;

	if ((s = ft_lexer_next(&self->lexer, 1, &tok)) < 0)
		MSH_EXIT(EXIT_FAILURE, self);
	if (next)
		*next = msh_peek(self);
	return (s == 1 ? tok : NULL);
}

inline t_tok	*msh_consume(t_msh *self, uint8_t id)
{
	t_tok	*tok;
	ssize_t	s;
	char	buf[20];

	if ((s = ft_lexer_next(&self->lexer, 1, &tok)) < 0)
		MSH_EXIT(EXIT_FAILURE, self);
	if (s && tok->id != id)
	{
		ft_puts(1, "unexpected token '");
		buf[ft_intstr(buf, tok->id, 10)] = 0;
		ft_puts(1, buf);
		ft_puts(1, "', expected ,");
		buf[ft_intstr(buf, id, 10)] = 0;
		ft_puts(1, buf);
		ft_putl(1, "'.");
		MSH_EXIT(EXIT_FAILURE, self);
	}
	return (s == 1 ? tok : NULL);
}
