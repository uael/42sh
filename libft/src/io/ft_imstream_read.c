/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imstream_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/io/imstream.h"

inline t_sz	ft_imstream_read(t_imstream *self, char *b, size_t len)
{
	if (!self->buf)
		return (ERR(errno = EINVAL));
	if (len > self->len)
		len = self->len;
	if (len)
	{
		if (b)
			ft_memcpy(b, self->buf + self->cur, len * sizeof(char));
		self->cur += len;
	}
	return (len);
}

t_sz		ft_imstream_readf(t_imstream *self, char *fmt, ...)
{
	va_list	ap;
	t_sz	n;

	va_start(ap, fmt);
	n = ft_imstream_vreadf(self, fmt, ap);
	va_end(ap);
	return (n);
}

inline t_sz	ft_imstream_vreadf(t_imstream *self, char *fmt, va_list ap)
{
	(void)self;
	(void)fmt;
	(void)ap;
	return (ERR(errno = ENIMPL));
}
