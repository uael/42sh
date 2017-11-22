/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/src_peek.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 11:45:41 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/src.h"

inline char		ft_src_peek(t_src *self, size_t n)
{
	return (ft_istream_peek(&self->in, n));
}

inline ssize_t	ft_src_get(t_src *self, char *buf, size_t n)
{
	return (ft_istream_get(&self->in, buf, n));
}

inline char		ft_src_nnext(t_src *self, size_t n, char *peek)
{
	char c;

	if (!n-- || !(c = ft_src_next(self, peek)))
		return ('\0');
	while (n--)
		ft_src_next(self, peek);
	return (c);
}

inline char		ft_src_next(t_src *self, char *peek)
{
	char c;

	if (!(c = ft_istream_getc(&self->in)))
		return (c);
	++self->cur.cur;
	if (c == '\r')
		return (ft_src_next(self, peek));
	if (c == '\v' || c == '\f' || c == '\n')
	{
		++self->cur.line;
		self->cur.col = 0;
		c = '\n';
	}
	++self->cur.col;
	if (peek)
		*peek = ft_src_peek(self, 0);
	return (c);
}
