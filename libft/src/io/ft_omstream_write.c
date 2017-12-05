/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omstream_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:21:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/omstream.h"

inline t_sz	ft_omstream_write(t_omstream *self, char const *sr, size_t len)
{
	if (!ft_du8_grow(self, len))
		return (ENO);
	ft_memcpy(self->buf + self->cur, sr, len);
	if ((self->cur += len) > self->len)
	{
		self->len = self->cur;
		self->buf[self->len] = '\0';
	}
	return (OK);
}

t_sz		ft_omstream_writef(t_omstream *self, char const *fmt, ...)
{
	va_list	ap;
	t_sz	sz;

	va_start(ap, fmt);
	sz = ft_omstream_vwritef(self, fmt, ap);
	va_end(ap);
	return (sz);
}

inline t_sz	ft_omstream_vwritef(t_omstream *self, char const *fmt, va_list ap)
{
	char	*sp;
	ssize_t	sz;
	char	buf[20];

	sz = 0;
	while ((sp = ft_strchr(fmt, '%')) &&
		(sz += ft_omstream_write(self, fmt, sp - fmt)) >= 0)
		if (*((fmt = ++sp + 1) - 1) == 'd')
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
	return (sz + ft_omstream_write(self, fmt, ft_strlen(fmt)));
}
