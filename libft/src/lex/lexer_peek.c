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

inline t_ret	ft_lexer_peek(t_lexer *self, size_t n, t_tok **peek)
{
	ssize_t s;

	if (ft_deq_size(&self->toks) < n + 1 &&
		(s = ft_lexer_scan(self, n + 1)) < (ssize_t)n + 1)
		return (s < 0 ? RET_ERR : RET_NOK);
	if (peek)
		*peek = (t_tok *)ft_deq_at(&self->toks, n);
	return (RET_OK);
}

inline ssize_t	ft_lexer_next(t_lexer *self, size_t n, t_tok **peek)
{
	ssize_t s;

	if (ft_deq_size(&self->toks) < n && (s = ft_lexer_scan(self, n)) <= 0)
		return (s < 0 ? -1 : 0);
	if (peek)
		*peek = (t_tok *)ft_deq_at(&self->toks, 0);
	return (ft_deq_shiftn(&self->toks, n, NULL));
}

inline size_t	ft_lexer_skip(t_lexer *self, size_t n, t_tok **out)
{
	return (ft_deq_shiftn(&self->toks, n, out));
}

inline t_ret	ft_lexer_match(t_tok *tok, t_src *src, size_t n, uint8_t id)
{
	tok->id = id;
	tok->val = NULL;
	if (ft_src_next(src, NULL, n) < 0)
		return (RET_ERR);
	return (RET_OK);
}
