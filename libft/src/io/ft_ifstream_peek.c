/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 19:25:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ifstream.h"

static inline t_st	ifs_alloc(t_ifstream *self)
{
	size_t	cap;
	void	*buf;

	cap = self->cap + FT_PAGE_SIZE + 1;
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(char),
		cap * sizeof(char))))
		return (ENO);
	self->buf = buf;
	self->cap = cap;
	return (OK);
}

static inline t_sz	ifs_bufferize(t_ifstream *self, size_t len)
{
	size_t	cur;
	size_t	cnt;
	t_sz	sz;

	cur = self->cur - self->beg;
	if (self->len - cur >= len)
		return (len);
	else
	{
		cnt = 0;
		while (self->len - cur < len)
		{
			if (self->cap - self->len < FT_PAGE_SIZE &&
				ST_NOK(sz = ifs_alloc(self)))
				return (ST_TOSZ(sz));
			if ((sz = read(self->fd, self->buf + self->len, FT_PAGE_SIZE)) == 0)
				break ;
			if (sz < 0)
				return (ENO);
			cnt += sz;
			self->len += sz;
			self->end += sz;
		}
		return (cnt > len ? len : cnt);
	}
}

inline char			ft_ifstream_getc(t_ifstream *self)
{
	char	c;
	t_sz	sz;

	if ((sz = ft_ifstream_read(self, &c, 1)) == 1)
		return (c);
	return ((char)SZ_TOST(sz));
}

inline t_sz			ft_ifstream_get(t_ifstream *self, char *buf, size_t n)
{
	t_sz sz;

	if (SZ_OK(sz = ifs_bufferize(self, n)))
		ft_memcpy(buf, self->buf + self->cur - self->beg, n);
	return (sz);
}

inline t_st			ft_ifstream_peek(t_ifstream *self, char *c, size_t n)
{
	t_sz sz;

	if ((sz = ifs_bufferize(self, n + 1)) < (t_sz)n + 1)
		return (SZ_TOST(sz));
	if (c)
		*c = self->buf[self->cur - self->beg + n];
	return (OK);
}
