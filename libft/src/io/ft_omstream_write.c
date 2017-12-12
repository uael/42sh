/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omstream_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 11:21:55 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/omstream.h"

inline size_t	ft_omstream_write(t_omstream *self, char const *sr, size_t len)
{
	ft_du8_grow(self, len);
	ft_memcpy(self->buf + self->cur, sr, len);
	if ((self->cur += len) > self->len)
	{
		self->len = self->cur;
		self->buf[self->len] = '\0';
	}
	return (len);
}

size_t			ft_omstream_writef(t_omstream *self, char const *fmt, ...)
{
	va_list	ap;
	size_t	sz;

	va_start(ap, fmt);
	sz = ft_omstream_vwritef(self, fmt, ap);
	va_end(ap);
	return (sz);
}

inline size_t	ft_omstream_vwritef(t_omstream *self, char const *f, va_list ap)
{
	char	*sp;
	size_t	sz;
	char	buf[20];

	sz = 0;
	while ((sp = ft_strchr(f, '%')) &&
		(sz += ft_omstream_write(self, f, sp - f)))
		if (*((f = ++sp + 1) - 1) == 'd')
			sz += ft_omstream_write(self, buf,
				ft_intstr(buf, va_arg(ap, int64_t), 10));
		else if (*sp == 'u')
			sz += ft_omstream_write(self, buf,
				ft_uintstr(buf, va_arg(ap, uint64_t), 10));
		else if (*sp == 's')
			sz += ft_omstream_puts(self, va_arg(ap, char *));
		else if (*sp == 'c')
			sz += ft_omstream_putc(self, (char)va_arg(ap, int));
		else if (*sp == 'f')
			sz += ft_omstream_write(self, buf,
				ft_floatstr(buf, (float)va_arg(ap, double), 10, 10));
		else if (*sp == 'e')
			sz += ft_omstream_puts(self, ft_strerr(va_arg(ap, int)));
	return (sz + ft_omstream_write(self, f, ft_strlen(f)));
}
