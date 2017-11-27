/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:50:09 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ifstream.h"

static inline int		ifs_alloc(t_ifstream *self)
{
	size_t	cap;
	void	*buf;

	cap = self->cap + FT_PAGE_SIZE;
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(char),
		cap * sizeof(char))))
		return (ST_ERRNO);
	self->buf = buf;
	self->cap = cap;
	return (ST_OK);
}

static inline ssize_t	ifs_bufferize(t_ifstream *self, size_t len)
{
	size_t	cur;
	size_t	cnt;
	ssize_t	st;

	cur = self->cur - self->beg;
	if (self->len - cur >= len)
		return (len);
	else
	{
		cnt = 0;
		while (self->len - cur < len)
		{
			if (self->cap - self->len < FT_PAGE_SIZE && (st = ifs_alloc(self)))
				return (st);
			if ((st = read(self->fd, self->buf + self->len, FT_PAGE_SIZE)) == 0)
				break ;
			if (st < 0)
				return (ST_ERRNO);
			cnt += st;
			self->len += st;
			self->end += st;
		}
		return (cnt > len ? len : cnt);
	}
}

inline char				ft_ifstream_getc(t_ifstream *self)
{
	char	c;
	ssize_t	s;

	if ((s = ft_ifstream_read(self, &c, 1)) == 1)
		return (c);
	return ((char)ST_HDL(s, 0));
}

inline ssize_t			ft_ifstream_get(t_ifstream *self, char *buf, size_t n)
{
	ssize_t l;

	if ((l = ifs_bufferize(self, n)) > 0)
		ft_memcpy(buf, self->buf + self->cur - self->beg, n);
	return (l);
}

inline int				ft_ifstream_peek(t_ifstream *self, char *c, size_t n)
{
	ssize_t s;

	if ((s = ifs_bufferize(self, n + 1)) < (ssize_t)n + 1)
		return ((int)ST_HDL(s, ST_NOK));
	if (c)
		*c = self->buf[self->cur - self->beg + n];
	return (ST_OK);
}
