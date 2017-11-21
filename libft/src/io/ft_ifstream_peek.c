/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ifstream.h"

static inline t_bool	ft_ifs_realloc(t_ifstream *self)
{
	size_t	cap;
	void	*buf;

	cap = self->cap + FT_PAGE_SIZE;
	if ((buf = ft_realloc(self->buf, self->len * sizeof(char),
		cap * sizeof(char))) == NULL)
		return (0);
	self->buf = buf;
	self->cap = cap;
	return (1);
}

static inline ssize_t	ft_ifs_bufferize(t_ifstream *self, size_t len)
{
	size_t	cur;
	size_t	b;
	ssize_t	r;

	cur = self->cur - self->beg;
	if (self->len - cur >= len)
		return (len);
	else
	{
		b = 0;
		while (self->len - cur < len)
		{
			if (self->cap - self->len < FT_PAGE_SIZE && !ft_ifs_realloc(self))
				return (-1);
			if ((r = read(self->fd, self->buf + self->len, FT_PAGE_SIZE)) == 0)
				break ;
			b += r;
			self->len += r;
			self->end += r;
		}
		return (b > len ? len : b);
	}
}

inline char				ft_ifstream_getc(t_ifstream *self)
{
	char c;

	if (ft_ifstream_read(self, &c, 1) == 1)
		return (c);
	return ('\0');
}

inline ssize_t			ft_ifstream_get(t_ifstream *self, char *buf, size_t len)
{
	ssize_t l;

	if ((l = ft_ifs_bufferize(self, len)) > 0)
		ft_memcpy(buf, self->buf + self->cur - self->beg, len);
	return (l);
}

inline char				ft_ifstream_peek(t_ifstream *self, size_t n)
{
	if ((ssize_t)n > ft_ifs_bufferize(self, n + 1))
		return ('\0');
	return (self->buf[self->cur - self->beg + n]);
}
