/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/tok_peek.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 11:21:55 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline int			ft_tok_peek(t_lexer *self, size_t n, t_tok **peek)
{
	ssize_t sz;

	if (ft_deq_size(&self->toks) < n + 1 &&
		(sz = ft_lexer_scan(self, n + 1)) < (ssize_t)n + 1)
		return (sz <= 0 ? (int)sz : NOP);
	if (peek)
		*peek = (t_tok *)ft_deq_at(&self->toks, n);
	return (YEP);
}

inline ssize_t		ft_tok_next(t_lexer *self, size_t n, t_tok **peek)
{
	ssize_t sz;

	if (ft_deq_size(&self->toks) < n && (sz = ft_lexer_scan(self, n)) <= 0)
		return (sz);
	if (peek)
		*peek = (t_tok *)ft_deq_at(&self->toks, 0);
	return (ft_deq_shiftn(&self->toks, n, NULL));
}

inline size_t		ft_tok_skip(t_lexer *self, size_t n, t_tok **out)
{
	return (ft_deq_shiftn(&self->toks, n, out));
}
