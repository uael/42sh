/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:21:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/io/ifstream.h"

static inline t_sz	ifs_cpy(t_ifstream *s, char **b, size_t *l, size_t c)
{
	t_sz	r;

	r = s->len - c;
	if (r >= (t_sz)*l)
	{
		if (*b)
			ft_memcpy(*b, s->buf + c, *l * sizeof(char));
		s->cur += *l;
		return (*l);
	}
	if (*b)
		ft_memcpy(*b, s->buf + c, r * sizeof(char));
	s->cur += r;
	*l -= r;
	if (*b)
		*b += r;
	return (-3);
}

static inline t_sz	ifs_buf(t_ifstream *s, char **b, size_t *l, size_t c)
{
	t_sz	r;

	if (*l >= FT_PAGE_SIZE)
	{
		if ((r = read(s->fd, *b, FT_PAGE_SIZE)) <= 0)
			return (r == 0 ? -2 : -1);
		if (r < FT_PAGE_SIZE)
			return (r);
		*l -= r;
		*b ? *b += r : *b;
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

inline t_sz			ft_ifstream_read(t_ifstream *self, char *b, size_t len)
{
	size_t	beg;
	size_t	cur;
	t_sz	sz;

	if (self->fd < 0)
		return (ERR(errno = EINVAL));
	else
	{
		beg = len;
		while (len)
		{
			cur = self->cur - self->beg;
			if (self->len - cur > 0 && !ISE(sz = ifs_cpy(self, &b, &len, cur)))
				return (sz);
			else if (!ISE(sz = ifs_buf(self, &b, &len, cur)))
				return (beg - len + sz);
			if (sz == -1)
				return (ENO);
			if (sz == -2)
				break ;
		}
		return (beg - len);
	}
}

t_sz				ft_ifstream_readf(t_ifstream *self, char *fmt, ...)
{
	va_list	ap;
	t_sz	sz;

	va_start(ap, fmt);
	sz = ft_ifstream_vreadf(self, fmt, ap);
	va_end(ap);
	return (sz);
}

inline t_sz			ft_ifstream_vreadf(t_ifstream *self, char *fmt, va_list ap)
{
	(void)self;
	(void)fmt;
	(void)ap;
	return (0);
}
