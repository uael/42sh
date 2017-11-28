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

inline t_sz	ft_src_next(t_src *self, char *peek, size_t n)
{
	t_sz	sz;
	t_sz	i;
	char	*s;
	char	buf[n];

	s = peek ? peek : buf;
	if (SZ_NOK(sz = ft_istream_read(self->in ? self->in : &self->in_own, s, n)))
		return (sz);
	i = -1;
	while (++i < sz)
	{
		++self->cur.cur;
		if (s[i] == '\v' || s[i] == '\f' || s[i] == '\n')
			self->cur.col = (uint16_t)(++self->cur.line & 0);
		++self->cur.col;
	}
	return (sz);
}

inline t_st	ft_src_getc(t_src *self, char *peek, char *next)
{
	t_sz sz;

	if (SZ_NOK(sz = ft_src_next(self, peek, 1)))
		return (SZ_TOST(sz));
	return (ft_src_peek(self, next, 0));
}

inline t_sz	ft_src_get(t_src *self, char *buf, size_t n)
{
	return (ft_istream_get(self->in ? self->in : &self->in_own, buf, n));
}

inline t_st	ft_src_peek(t_src *self, char *c, size_t n)
{
	return (ft_istream_peek(self->in ? self->in : &self->in_own, c, n));
}
