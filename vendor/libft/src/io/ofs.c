/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

void		ft_ofsctor(t_ofs *self, int ofd)
{
	self->ofd = ofd;
	self->i = 0;
}

ssize_t		ft_ofsflush(t_ofs *self)
{
	ssize_t	sz;

	if (!self->i)
		return (0);
	sz = ft_write(self->ofd, self->buf, self->i);
	self->i = 0;
	return (sz);
}

ssize_t		ft_ofswrc(t_ofs *self, unsigned char c)
{
	self->buf[self->i++] = c;
	if (self->i == FT_PAGE_SIZE && ft_ofsflush(self) < 0)
		return (WUT);
	return (YEP);
}

ssize_t		ft_ofswr(t_ofs *self, void const *buf, size_t n)
{
	uint8_t const	*cbuf;
	ssize_t			sz;

	cbuf = buf;
	sz = 0;
	while (n)
	{
		if (ft_ofswrc(self, *cbuf++))
			return (WUT);
		++sz;
		--n;
	}
	return (sz);
}

ssize_t		ft_ofswrs(t_ofs *self, char const *buf)
{
	return (ft_ofswr(self, buf, ft_strlen(buf)));
}

ssize_t		ft_ofswrl(t_ofs *self, long i, uint8_t base)
{
	char	buf[21];

	return (ft_ofswr(self, buf, ft_intstr(buf, i, base)));
}

ssize_t		ft_ofswrul(t_ofs *self, ulong i, uint8_t base)
{
	char	buf[21];

	return (ft_ofswr(self, buf, ft_uintstr(buf, i, base)));
}

ssize_t		ft_ofswrd(t_ofs *self, double i, int precision, uint8_t base)
{
	char	buf[21];

	return (ft_ofswr(self, buf, ft_floatstr(buf, i, precision, base)));
}

ssize_t		ft_ofsvwrf(t_ofs *self, char const *f, va_list ap)
{
	char	*sp;
	ssize_t	sz;

	sz = 0;
	while ((sp = ft_strchr(f, '%')) && (sz += ft_ofswr(self, f, sp - f)) >= 0)
		if (*((f = ++sp + 1) - 1) == 'd')
			sz += ft_ofswrl(self, va_arg(ap, long), 10);
		else if (*sp == 'u')
			sz += ft_ofswrul(self, va_arg(ap, ulong), 10);
		else if (*sp == 's')
			sz += ft_ofswrs(self, va_arg(ap, char const *));
		else if (*sp == 'c')
			sz += ft_ofswrc(self, (unsigned char) va_arg(ap, int));
		else if (*sp == 'f')
			sz += ft_ofswrd(self, va_arg(ap, double), 10, 10);
		else if (*sp == 'e')
			sz += ft_ofswrs(self, ft_strerr(va_arg(ap, int)));
	return (sz + ft_ofswrs(self, f));
}

ssize_t		ft_ofswrf(t_ofs *self, char const *fmt, ...)
{
	va_list	ap;
	ssize_t	sz;

	va_start(ap, fmt);
	sz = ft_ofsvwrf(self, fmt, ap);
	va_end(ap);
	return (sz);
}
