/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofs_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:02:13 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

ssize_t			ft_ofsvwrf(t_ofs *self, char const *f, va_list ap)
{
	char	*sp;
	ssize_t	sz;

	sz = 0;
	while ((sp = ft_strchr(f, '%')) && (sz += ft_ofswr(self, f, sp - f)) >= 0)
		if (*((f = ++sp + 1) - 1) == 'd')
			sz += ft_ofswrl(self, va_arg(ap, long), 10);
		else if (*sp == 'u')
			sz += ft_ofswrul(self, va_arg(ap, unsigned long), 10);
		else if (*sp == 's')
			sz += ft_ofswrs(self, va_arg(ap, char const *));
		else if (*sp == 'c')
			sz += ft_ofswrc(self, (unsigned char)va_arg(ap, int));
		else if (*sp == 'f')
			sz += ft_ofswrd(self, va_arg(ap, double), 10, 10);
		else if (*sp == 'e')
			sz += ft_ofswrs(self, ft_strerr(va_arg(ap, int)));
	return (sz + ft_ofswrs(self, f));
}

ssize_t			ft_ofswrf(t_ofs *self, char const *fmt, ...)
{
	va_list ap;
	ssize_t sz;

	va_start(ap, fmt);
	sz = ft_ofsvwrf(self, fmt, ap);
	va_end(ap);
	return (sz);
}
