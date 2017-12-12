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
#include "libft/ex.h"

static inline void		ifs_alloc(t_ifstream *self)
{
	size_t	cap;
	void	*buf;

	cap = self->cap + FT_PAGE_SIZE + 1;
	buf = ft_realloc(self->buf, self->len * sizeof(char), cap * sizeof(char));
	self->buf = buf;
	self->cap = cap;
}

static inline ssize_t	ifs_bufferize(t_ifstream *self, size_t len)
{
	size_t	cur;
	size_t	cnt;
	ssize_t	sz;

	cur = self->cur - self->beg;
	if (self->len - cur >= len)
		return (len);
	else
	{
		cnt = 0;
		while (self->len - cur < len)
		{
			if (self->cap - self->len < FT_PAGE_SIZE)
				ifs_alloc(self);
			if ((sz = read(self->fd, self->buf + self->len, FT_PAGE_SIZE)) == 0)
				break ;
			if (sz < 0)
				return (THROW(WUT));
			cnt += sz;
			self->len += sz;
			self->end += sz;
		}
		return (cnt > len ? len : cnt);
	}
}

inline char				ft_ifstream_getc(t_ifstream *self)
{
	char	c;
	ssize_t	sz;

	if ((sz = ft_ifstream_read(self, &c, 1)) == 1)
		return (c);
	return (sz < 0 ? (char)sz : (char)0);
}

inline ssize_t			ft_ifstream_get(t_ifstream *self, char *buf, size_t n)
{
	ssize_t sz;

	if ((sz = ifs_bufferize(self, n)) > 0)
		ft_memcpy(buf, self->buf + self->cur - self->beg, n);
	return (sz);
}

inline int				ft_ifstream_peek(t_ifstream *self, char *c, size_t n)
{
	ssize_t sz;

	if ((sz = ifs_bufferize(self, n + 1)) < (ssize_t)n + 1)
		return (sz < 0 ? (int)sz : 0);
	if (c)
		*c = self->buf[self->cur - self->beg + n];
	return (YEP);
}
