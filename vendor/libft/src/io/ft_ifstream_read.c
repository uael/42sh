/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 15:50:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/ex.h"
#include "libft/io.h"
#include "libft/io/ifstream.h"

static inline ssize_t	ifs_cpy(t_ifstream *s, char **b, size_t *l, size_t c)
{
	ssize_t	r;

	r = s->len - c;
	if (r >= (ssize_t)*l)
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

static inline ssize_t	ifs_buf(t_ifstream *s, char **b, size_t *l)
{
	ssize_t	r;

	if (*l >= FT_PAGE_SIZE)
	{
		if ((r = ft_read(s->fd, *b, FT_PAGE_SIZE)) <= 0)
			return (r == 0 ? -2 : WUT);
		if (r < FT_PAGE_SIZE)
			return (r);
		(void)((*l -= r) && (*b ? *b += r : *b));
	}
	else
	{
		s->beg += s->len;
		if (s->cap < FT_PAGE_SIZE)
		{
			s->buf = ft_malloc(FT_PAGE_SIZE * sizeof(char));
			s->cap = FT_PAGE_SIZE;
		}
		if ((r = ft_read(s->fd, s->buf, FT_PAGE_SIZE)) < 0)
			return (WUT);
		return ((s->len = (size_t)r) == 0 ? -2 :
			ifs_cpy(s, b, l, s->beg - s->cur));
	}
	return (-3);
}

inline ssize_t			ft_ifstream_read(t_ifstream *self, char *b, size_t len)
{
	size_t	beg;
	size_t	cur;
	ssize_t	sz;

	if (self->fd < 0)
		return (ENO_THROW(WUT, EINVAL));
	beg = len;
	while (len)
	{
		cur = self->cur - self->beg;
		if (self->len - cur > 0 && (sz = ifs_cpy(self, &b, &len, cur)) >= 0)
			return (sz);
		else if ((sz = ifs_buf(self, &b, &len)) >= 0)
			return (beg - len + sz);
		if (sz == WUT)
			return (WUT);
		if (sz == -2)
			break ;
	}
	return (beg - len);
}

ssize_t					ft_ifstream_readf(t_ifstream *self, char *fmt, ...)
{
	va_list	ap;
	ssize_t	sz;

	va_start(ap, fmt);
	sz = ft_ifstream_vreadf(self, fmt, ap);
	va_end(ap);
	return (sz);
}

inline ssize_t			ft_ifstream_vreadf(t_ifstream *self, char *f,va_list ap)
{
	(void)self;
	(void)f;
	(void)ap;
	return (0);
}
