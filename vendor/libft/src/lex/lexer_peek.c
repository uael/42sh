/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_peek.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"
#include "private.h"

inline ssize_t	ft_lexer_next(t_lexer *self, char *peek, size_t n)
{
	ssize_t st;

	if (!self->src && !(self->src = ft_lexer_src(self)))
		return (0);
	if ((st = ft_src_next(self->src, peek, n)) < 0)
		return (st);
	if (st || !self->srcs.len)
		return (st);
	ft_deq_shift(&self->srcs, NULL);
	self->src = NULL;
	return (ft_lexer_next(self, peek, n));
}

inline int		ft_lexer_peek(t_lexer *self, char *peek, size_t n)
{
	int		st;
	char	c;

	if (!self->src && !(self->src = ft_lexer_src(self)))
		return (NOP);
	if (n)
		return (ft_src_peek(self->src, peek, n));
	st = ft_src_peek(self->src, &c, n);
	if (peek)
		*peek = c;
	if (!st && c)
		return (st);
	ft_deq_shift(&self->srcs, NULL);
	self->src = NULL;
	return (ft_lexer_peek(self, peek, n));
}

inline int		ft_lexer_getc(t_lexer *self, char *peek, char *next)
{
	if (ft_lexer_next(self, peek, 1) < 0)
		return (WUT);
	return (ft_lexer_peek(self, next, 0));
}
