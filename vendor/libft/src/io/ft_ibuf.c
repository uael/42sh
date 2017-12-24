/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ibuf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

inline void	ft_ifsctor(t_ifs *self, int ifd, char *buf, size_t sz)
{
	self->ifd = ifd;
	self->i = 0;
	self->rd = 0;
	self->mcap = 0;
	self->sz = sz;
	self->buf = buf;
	self->mem = NULL;
}

char		ft_ifspeek(t_ifs *self, size_t i)
{
	char	*buf;
	ssize_t	sz;

	if ((sz = ft_ifsbuf(self, i, &buf)) <= 0)
		return ((char)(sz < 0 ? WUT : '\0'));
	return (buf[i]);
}

ssize_t		ft_ifsbuf(t_ifs *self, size_t sz, char **out)
{
	ssize_t	rd;
	size_t	left;
	char	*b;

	if (!self->rd || self->i == self->rd)
	{
		if ((rd = ft_read(self->ifd, self->buf, self->sz)) <= 0)
			return (rd ? WUT : 0);
		self->rd = (size_t)rd;
	}
	b = (self->mem ? self->mem : self->buf) + self->i;
	out ? *out = b : 0;
	while ((left = self->rd - self->i) < sz)
	{
		if ((self->rd % self->sz) != 0)
			return (left);
		b = ft_bufaver(self->mem, self->rd + self->sz, self->rd, sizeof(char));
		out ? *out = b : 0;
		self->mem = self->mem ? b : ft_memcpy(b, self->buf, self->sz);
		if ((rd = ft_read(self->ifd, self->mem + self->rd, self->sz)) <= 0)
			return (rd ? (size_t)WUT : left);
		self->rd += rd;
	}
	return (sz);
}

ssize_t		ft_ifsrd(t_ifs *s, void *b, size_t n)
{
	size_t	beg;
	ssize_t	r;
	char	*src;

	beg = n;
	src = s->mem ? s->mem : s->buf;
	while (n)
	{
		if (s->rd - s->i > 0 && (s->i += (r = ft_i64min(n, s->rd - s->i))))
			b ? ft_memcpy(b, src + s->i - r, (size_t)r) : 0;
		else if (n >= s->sz && (r = ft_read(s->ifd, b, s->sz)) < (ssize_t)s->sz)
			return (r < 0 ? (size_t)WUT : beg - (n - r));
		if (!(n -= r))
			break ;
		b ? b += r : 0;
		if (n < s->sz)
		{
			s->i = 0;
			s->rd = 0;
			if ((r = ft_read(s->ifd, src, s->sz)) <= 0)
				return (r ? (size_t)WUT : beg - n);
			s->rd = (size_t)r;
		}
	}
	return (beg - n);
}

ssize_t		ft_ifschr(t_ifs *self, char c, char **out)
{
	ssize_t	rd;
	char	*b;
	char	*chr;

	if (!self->rd || self->i == self->rd)
	{
		if ((rd = ft_read(self->ifd, self->buf, self->sz)) <= 0)
			return (rd ? WUT : 0);
		self->rd = (size_t)rd;
	}
	b = (self->mem ? self->mem : self->buf) + self->i;
	out ? *out = b : 0;
	while (!(chr = ft_strchr(b, c)))
	{
		if ((self->rd % self->sz) != 0)
			return (self->rd - self->i);
		b = ft_bufaver(self->mem, self->rd + self->sz, self->rd, sizeof(char));
		self->mem = self->mem ? b : ft_memcpy(b, self->buf, self->sz);
		out ? *out = b + self->i : 0;
		if ((rd = ft_read(self->ifd, self->mem + self->rd, self->sz)) <= 0)
			return (rd ? (size_t)WUT : self->rd - self->i);
		self->rd += rd;
	}
	return (chr - b + 1);
}
