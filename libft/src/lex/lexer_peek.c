/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_peek.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:58:15 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline t_st		ft_lexer_peek(t_lexer *self, size_t n, t_tok **peek)
{
	t_sz sz;

	if (ft_deq_size(&self->toks) < n + 1 &&
		(sz = ft_lexer_scan(self, n + 1)) < (t_sz)n + 1)
		return (SZ_TOST(sz));
	if (peek)
		*peek = (t_tok *)ft_deq_at(&self->toks, n);
	return (OK);
}

inline t_sz		ft_lexer_next(t_lexer *self, size_t n, t_tok **peek)
{
	t_sz sz;

	if (ft_deq_size(&self->toks) < n && SZ_NOK(sz = ft_lexer_scan(self, n)))
		return (sz);
	if (peek)
		*peek = (t_tok *)ft_deq_at(&self->toks, 0);
	return (ft_deq_shiftn(&self->toks, n, NULL));
}

inline size_t	ft_lexer_skip(t_lexer *self, size_t n, t_tok **out)
{
	return (ft_deq_shiftn(&self->toks, n, out));
}

inline t_st		ft_lexer_match(t_tok *tok, t_src *src, size_t n, uint8_t id)
{
	t_sz sz;

	tok->id = id;
	tok->val = NULL;
	if (SZ_NOK(sz = ft_src_next(src, NULL, n)))
		return (SZ_TOST(sz));
	return (OK);
}
