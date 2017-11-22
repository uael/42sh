/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_peek.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 13:07:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline t_tok		*ft_lexer_peek(t_lexer *self, size_t n)
{
	if (self->toks.len < n && ft_lexer_scan(self, n) < (ssize_t)n)
		return (NULL);
	return (ft_vec_at(&self->toks, n));
}

inline t_bool		ft_lexer_next(t_lexer *self, t_tok *peek)
{
	if (self->toks.len < 1 && ft_lexer_scan(self, 1) < 1)
		return (0);
	return (ft_vec_shift(&self->toks, peek ? peek : NULL));
}

inline size_t		ft_lexer_skip(t_lexer *self, size_t n, t_tok *out)
{
	return (ft_vec_shiftn(&self->toks, n, out));
}
