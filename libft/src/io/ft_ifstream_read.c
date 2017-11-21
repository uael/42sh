/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/io/ifstream.h"

static inline ssize_t	ifs_cpy(t_ifstream *s, char **b, size_t *l, size_t c)
{
	ssize_t	r;

	r = s->len - c;
	if (r > *l)
	{
		ft_memcpy(*b, s->buf + c, *l * sizeof(char));
		s->cur += *l;
		return (*l);
	}
	ft_memcpy(*b, s->buf + c, r * sizeof(char));
	s->cur += r;
	*l -= r;
	*b += r;
	return (-3);
}

static inline ssize_t	ifs_buf(t_ifstream *s, char **b, size_t *l, size_t c)
{
	ssize_t	r;

	if (*l >= FT_PAGE_SIZE)
	{
		if ((r = read(s->fd, *b, FT_PAGE_SIZE)) <= 0)
			return (r == 0 ? -2 : -1);
		if (r < FT_PAGE_SIZE)
			return (r);
		*l -= r;
		*b += r;
	}
	else
	{
		s->beg += s->len;
		if (s->cap < FT_PAGE_SIZE)
		{
			if (!(s->buf = malloc(FT_PAGE_SIZE * sizeof(char))))
				return (-1);
			s->cap = FT_PAGE_SIZE;
		}
		if ((r = read(s->fd, s->buf, FT_PAGE_SIZE)) < 0)
			return (-1);
		return ((s->len = (size_t)r) == 0 ? -2 : ifs_cpy(s, b, l, c));
	}
	return (-3);
}

inline ssize_t			ft_ifstream_read(t_ifstream *self, char *b, size_t len)
{
	size_t	cur;
	ssize_t	r;
	char	*beg;

	if (!self->filename || self->fd < 0)
		return (0);
	else
	{
		beg = b;
		while (len)
		{
			cur = self->cur - self->beg;
			if (self->len - cur > 0 && (r = ifs_cpy(self, &b, &len, cur)) >= 0)
				return (r);
			else if ((r = ifs_buf(self, &b, &len, cur)) >= 0)
				return (b - beg + r);
			if (r == -1)
				return (-1);
			if (r == -2)
				break ;
		}
		return (b - beg);
	}
}

ssize_t					ft_ifstream_readf(t_ifstream *self, char *fmt, ...)
{
	va_list	ap;
	ssize_t	n;

	va_start(ap, fmt);
	n = ft_ifstream_vreadf(self, fmt, ap);
	va_end(ap);
	return (n);
}

inline ssize_t			ft_ifstream_vreadf(t_ifstream *self, char *fmt,
	va_list ap)
{
	(void)self;
	(void)fmt;
	(void)ap;
	return (0);
}
