/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/src_peek.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 17:48:49 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/src.h"

inline ssize_t		ft_src_next(t_src *self, char *peek, size_t n)
{
	ssize_t s;
	ssize_t i;
	char	*p;
	char	b[n];

	p = peek ? peek : b;
	if ((s = ft_istream_read(self->in ? self->in : &self->in_own, p, n)) < 0)
		return (s);
	i = -1;
	while (++i < s)
	{
		++self->cur.cur;
		if (p[i] == '\v' || p[i] == '\f' || p[i] == '\n')
			self->cur.col = (uint16_t)(++self->cur.line & 0);
		++self->cur.col;
	}
	return (s);
}

inline ssize_t	ft_src_get(t_src *self, char *buf, size_t n)
{
	return (ft_istream_get(self->in ? self->in : &self->in_own, buf, n));
}

inline t_ret	ft_src_peek(t_src *self, char *c, size_t n)
{
	return (ft_istream_peek(self->in ? self->in : &self->in_own, c, n));
}
