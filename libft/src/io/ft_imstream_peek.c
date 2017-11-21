/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imstream_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/imstream.h"

inline char		ft_imstream_getc(t_imstream *self)
{
	if (self->len - self->cur)
		return (self->buf[self->cur++]);
	return ('\0');
}

inline ssize_t	ft_imstream_get(t_imstream *self, char *buf, size_t len)
{
	if (len > self->len)
		len = self->len;
	if (len)
		ft_memcpy(buf, self->buf + self->cur, len * sizeof(char));
	return (len);
}

inline char		ft_imstream_peek(t_imstream *self, size_t n)
{
	size_t cur;

	cur = self->cur + n;
	if (cur <= self->len)
		return (self->buf[cur]);
	return ('\0');
}
