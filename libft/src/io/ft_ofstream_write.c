/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ofstream_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:21:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ofstream.h"

inline t_sz	ft_ofstream_write(t_ofstream *s, char const *sr, size_t len)
{
	char const	*beg;
	size_t		b;
	size_t		c;
	ssize_t		sz;

	beg = sr;
	while (len)
	{
		if (!s->len)
			while (len >= FT_PAGE_SIZE)
			{
				if (SZ_NOK(sz = write(s->fd, sr, FT_PAGE_SIZE)))
					return (sz);
				((len -= sz) && (sr += sz));
			}
		b = FT_PAGE_SIZE - s->len > len ? len : FT_PAGE_SIZE - s->len;
		if (!s->buf && !(s->buf = malloc(FT_PAGE_SIZE * sizeof(char))))
			return (ENO);
		ft_memcpy(s->buf + (c = s->cur - s->beg), sr, (size_t)b * sizeof(char));
		((s->cur += b) && (c += b) > s->len && (s->len = c) && (s->end += b));
		((len -= b) && (sr += b));
		(s->len == FT_PAGE_SIZE ? ft_ofstream_flush(s) : (void)0);
	}
	return (sr - beg);
}

t_sz		ft_ofstream_writef(t_ofstream *self, char const *fmt, ...)
{
	va_list	ap;
	t_sz	sz;

	va_start(ap, fmt);
	sz = ft_ofstream_vwritef(self, fmt, ap);
	va_end(ap);
	return (sz);
}

inline t_sz	ft_ofstream_vwritef(t_ofstream *self, char const *fmt, va_list ap)
{
	char	*sp;
	ssize_t	sz;
	char	buf[20];

	sz = 0;
	while ((sp = ft_strchr(fmt, '%')) &&
		(sz += ft_ofstream_write(self, fmt, sp - fmt)) >= 0)
		if (*((fmt = ++sp + 1) - 1) == 'd')
			sz += ft_ofstream_write(self, buf,
				ft_intstr(buf, va_arg(ap, int64_t), 10));
		else if (*sp == 'u')
			sz += ft_ofstream_write(self, buf,
				ft_uintstr(buf, va_arg(ap, uint64_t), 10));
		else if (*sp == 's')
			sz += ft_ofstream_puts(self, va_arg(ap, char *));
		else if (*sp == 'c')
			sz += ft_ofstream_putc(self, (char)va_arg(ap, int));
		else if (*sp == 'f')
			sz += ft_ofstream_write(self, buf,
				ft_floatstr(buf, (float)va_arg(ap, double), 10, 10));
		else if (*sp == 'e')
			sz += ft_ofstream_puts(self, ft_strerr(va_arg(ap, int)));
	return (sz + ft_ofstream_write(self, fmt, ft_strlen(fmt)));
}
