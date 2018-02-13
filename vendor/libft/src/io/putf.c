/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

ssize_t			ft_putf(int fd, char const *fmt, ...)
{
	va_list	ap;
	ssize_t	n;

	va_start(ap, fmt);
	n = ft_vputf(fd, fmt, ap);
	va_end(ap);
	return (n);
}

inline ssize_t	ft_vputf(int fd, char const *f, va_list ap)
{
	char	*sp;
	ssize_t	sz;

	sz = 0;
	while ((sp = ft_strchr(f, '%')) && (sz += ft_write(fd, f, sp - f)) >= 0)
		if (*((f = ++sp + 1) - 1) == 'd')
			sz += ft_putn(fd, va_arg(ap, int64_t), 10);
		else if (*sp == 'u')
			sz += ft_putu(fd, va_arg(ap, uint64_t), 10);
		else if (*sp == 's')
			sz += ft_puts(fd, va_arg(ap, char const *));
		else if (*sp == 'c')
			sz += ft_putc(fd, (char)va_arg(ap, int));
		else if (*sp == 'f')
			sz += ft_putd(fd, (float)va_arg(ap, double), 10, 10);
		else if (*sp == 'e')
			sz += ft_puts(fd, ft_strerr(va_arg(ap, int)));
	return (sz + ft_write(fd, f, ft_strlen(f)));
}
