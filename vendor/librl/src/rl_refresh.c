/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_refresh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "rl.h"

typedef struct	s_obuf
{
	int			ofd;
	char		*buf;
	size_t		i;
	size_t		sz;
}				t_obuf;

void		ft_obuf_ctor(t_obuf *self, int ofd, char *buf, size_t sz)
{
	self->ofd = ofd;
	self->buf = buf;
	self->i = 0;
	self->sz = sz;
}

ssize_t		ft_obuf_flush(t_obuf *self)
{
	ssize_t	sz;

	sz = ft_write(self->ofd, self->buf, self->i);
	self->i = 0;
	return (sz);
}

ssize_t		ft_wrc(t_obuf *self, unsigned char c)
{
	self->buf[self->i++] = c;
	if (self->i == self->sz && ft_obuf_flush(self) < 0)
		return (WUT);
	return (YEP);
}

ssize_t		ft_wr(t_obuf *self, void const *buf, size_t n)
{
	uint8_t const	*cbuf;
	ssize_t			sz;

	cbuf = buf;
	sz = 0;
	while (n)
	{
		if (ft_wrc(self, *cbuf++))
			return (WUT);
		++sz;
		--n;
	}
	return (sz);
}

ssize_t		ft_wrs(t_obuf *self, char const *buf)
{
	return (ft_wr(self, buf, ft_strlen(buf)));
}

ssize_t		ft_wrl(t_obuf *self, long i, uint8_t base)
{
	char	buf[21];

	return (ft_wr(self, buf, ft_intstr(buf, i, base)));
}

ssize_t		ft_wrul(t_obuf *self, ulong i, uint8_t base)
{
	char	buf[21];

	return (ft_wr(self, buf, ft_uintstr(buf, i, base)));
}

ssize_t		ft_wrd(t_obuf *self, double i, int precision, uint8_t base)
{
	char	buf[21];

	return (ft_wr(self, buf, ft_floatstr(buf, i, precision, base)));
}

ssize_t		ft_vwrf(t_obuf *self, char const *f, va_list ap)
{
	char	*sp;
	ssize_t	sz;

	sz = 0;
	while ((sp = ft_strchr(f, '%')) && (sz += ft_wr(self, f, sp - f)) >= 0)
		if (*((f = ++sp + 1) - 1) == 'd')
			sz += ft_wrl(self, va_arg(ap, long), 10);
		else if (*sp == 'u')
			sz += ft_wrul(self, va_arg(ap, ulong), 10);
		else if (*sp == 's')
			sz += ft_wrs(self, va_arg(ap, char const *));
		else if (*sp == 'c')
			sz += ft_wrc(self, (unsigned char)va_arg(ap, int));
		else if (*sp == 'f')
			sz += ft_wrd(self, va_arg(ap, double), 10, 10);
		else if (*sp == 'e')
			sz += ft_wrs(self, ft_strerr(va_arg(ap, int)));
	return (sz + ft_wrs(self, f));
}

ssize_t		ft_wrf(t_obuf *self, char const *fmt, ...)
{
	va_list	ap;
	ssize_t	sz;

	va_start(ap, fmt);
	sz = ft_vwrf(self, fmt, ap);
	va_end(ap);
	return (sz);
}

void	rl_refresh(t_rl *self)
{
	char	buf[FT_PAGE_SIZE];
	t_obuf	*obuf;
	int		rows;
	int		rpos;
	int		rpos2;
	int		col;
	int		old_rows;
	int		j;

	obuf = alloca(sizeof(t_obuf));
	ft_obuf_ctor(obuf, self->ofd, buf, FT_PAGE_SIZE);
	rows = (self->plen + self->len + self->cols - 1) / self->cols;
	rpos = (self->plen + self->oldpos + self->cols) / self->cols;
	old_rows = self->mrows;
	if (rows > self->mrows)
		self->mrows = rows;
	if (old_rows-rpos > 0)
		ft_wrf(obuf, "\x1b[%dB", old_rows - rpos);
	for (j = 0; j < old_rows-1; j++)
		ft_wr(obuf, "\r\x1b[0K\x1b[1A", sizeof("\r\x1b[0K\x1b[1A") - 1);
	ft_wr(obuf, "\r\x1b[0K", sizeof("\r\x1b[0K") - 1);
	ft_wr(obuf, self->prompt, (size_t)self->plen);
	ft_wr(obuf, self->buf, (size_t)self->len);
	if (self->pos && self->pos == self->len &&
		(self->pos + self->plen) % self->cols == 0)
	{
		ft_wr(obuf, "\n", 1);
		rows++;
		if (rows > self->mrows)
			self->mrows = rows;
	}
	rpos2 = (self->plen + self->pos + self->cols) / self->cols;
	if (rows-rpos2 > 0)
		ft_wrf(obuf, "\x1b[%dA", rows - rpos2);
	col = (self->plen + self->pos) % self->cols;
	if (col)
		ft_wrf(obuf, "\r\x1b[%dC", col);
	else
		ft_wr(obuf, "\r", 1);
	self->oldpos = self->pos;
	ft_obuf_flush(obuf);
}
