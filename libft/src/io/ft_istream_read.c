/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istream_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/io/istream.h"

inline ssize_t	ft_istream_read(t_istream *self, char *b, size_t len)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_read(&self->u.file, b, len));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_read(&self->u.mem, b, len));
	return (RET_ERR);
}

ssize_t			ft_istream_readf(t_istream *self, char *fmt, ...)
{
	va_list	ap;
	ssize_t	n;

	va_start(ap, fmt);
	n = ft_istream_vreadf(self, fmt, ap);
	va_end(ap);
	return (n);
}

inline ssize_t	ft_istream_vreadf(t_istream *self, char *fmt, va_list ap)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_vreadf(&self->u.file, fmt, ap));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_vreadf(&self->u.mem, fmt, ap));
	return (RET_ERR);
}
