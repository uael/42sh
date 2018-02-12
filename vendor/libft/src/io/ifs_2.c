/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

#define BSZ FT_PAGE_SIZE

static inline ssize_t	ifsbuf(t_ifs *self, char **out)
{
	char	buf[BSZ + 1];
	ssize_t	rd;
	size_t	left;

	left = self->rd - self->i;
	if ((self->rd % BSZ) != 0)
		return (left);
	if ((rd = ft_read(self->ifd, buf, BSZ)) <= 0)
		return (rd ? (size_t)WUT : left);
	*out = self->buf ? self->buf : self->stack;
	if (rd <= (ssize_t)self->i)
		ft_memmove(*out, *out + self->i, left);
	else
	{
		*out = ft_memcpy(ft_malloc(self->rd + BSZ + 1),
			*out + self->i, left);
		self->buf ? free(self->buf) : 0;
		self->buf = *out;
		*out = self->buf;
	}
	ft_memcpy(*out + left, buf, (size_t)rd);
	self->rd = left + rd;
	(*out)[self->rd] = '\0';
	return (self->i = 0);
}

ssize_t					ft_ifsbuf(t_ifs *self, size_t sz, char **out)
{
	ssize_t	rd;
	char	*src;

	if (!self->rd || self->i == self->rd)
	{
		if ((rd = ft_read(self->ifd, self->stack, BSZ)) <= 0)
			return (rd ? WUT : 0);
		self->i = 0;
		self->rd = (size_t)rd;
	}
	src = (self->buf ? self->buf : self->stack) + self->i;
	out ? *out = src : 0;
	while (self->rd - self->i < sz)
		if ((rd = ifsbuf(self, &src)))
		{
			if (rd > 0 && out)
				*out = src;
			return (rd);
		}
	if (out)
		*out = src;
	return (sz);
}

ssize_t					ft_ifsrd(t_ifs *s, void *b, size_t n)
{
	size_t	beg;
	ssize_t	r;
	char	*src;

	beg = n;
	src = s->buf ? s->buf : s->stack;
	while ((r = n))
	{
		if (s->rd - s->i > 0 && (s->i += (r = ft_i64min(n, s->rd - s->i))))
			b ? ft_memcpy(b, src + s->i - r, (size_t)r) : 0;
		else if (n >= BSZ && (r = ft_read(s->ifd, b, BSZ)) < BSZ)
			return (r < 0 ? (size_t)WUT : beg - (n - r));
		if (!(n -= r))
			break ;
		b ? b += r : 0;
		if (n < BSZ)
		{
			s->i = 0;
			s->rd = 0;
			if ((r = ft_read(s->ifd, src, BSZ)) <= 0)
				return (r ? (size_t)WUT : beg - n);
			s->rd = (size_t)r;
		}
	}
	return (beg - n);
}

ssize_t					ft_ifschr(t_ifs *self, size_t off, char c, char **out)
{
	ssize_t	rd;
	char	*src;
	char	*chr;

	if (off > self->rd - self->i)
		return (WUT);
	if (!self->rd || self->i == self->rd)
	{
		if ((rd = ft_read(self->ifd, self->stack, BSZ)) <= 0)
			return (rd ? WUT : 0);
		self->i = 0;
		self->rd = (size_t)rd;
	}
	src = (self->buf ? self->buf : self->stack) + off + self->i;
	while (!(chr = ft_strchr(src, c)))
		if ((rd = ifsbuf(self, &src)))
		{
			if (rd > 0 && out)
				*out = src;
			return (rd);
		}
	if (out)
		*out = src;
	return (chr - src + 1);
}
