/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_peek.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 16:06:42 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline int8_t	ft_lexer_peek(t_lexer *self, size_t n, t_tok *peek)
{
	ssize_t s;

	if (self->toks.len < n && (s = ft_lexer_scan(self, n)) < (ssize_t)n)
		return ((int8_t)(s < 0 ? -1 : 1));
	if (peek)
		*peek = *(t_tok *)ft_vec_at(&self->toks, n);
	return (0);
}

inline ssize_t	ft_lexer_next(t_lexer *self, size_t n, t_tok *peek)
{
	ssize_t s;

	if (self->toks.len < n && (s = ft_lexer_scan(self, n)) <= 0)
		return (s < 0 ? -1 : 0);
	if (peek)
		*peek = *(t_tok *)ft_vec_at(&self->toks, 0);
	return (ft_vec_shiftn(&self->toks, n, NULL));
}

inline size_t	ft_lexer_skip(t_lexer *self, size_t n, t_tok *out)
{
	return (ft_vec_shiftn(&self->toks, n, out));
}
