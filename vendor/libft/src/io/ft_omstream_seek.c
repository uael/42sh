/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omstream_peek.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 10:02:14 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libft/io/omstream.h"

inline void		ft_omstream_flush(t_omstream *self, int fd)
{
	size_t l;

	if (self->cur)
	{
		l = self->cur;
		self->len = 0;
		self->cur = 0;
		ft_write(fd, self->buf, l);
	}
}

inline t_bool	ft_omstream_rewind(t_omstream *self, size_t n)
{
	if (n > self->cur)
		return (FALSE);
	self->cur -= n;
	return (TRUE);
}

inline t_bool	ft_omstream_forward(t_omstream *self, size_t n)
{
	if (self->cur + n > self->len)
		return (FALSE);
	self->cur += n;
	return (TRUE);
}

inline t_bool	ft_omstream_seek(t_omstream *self, size_t off)
{
	if (self->cur > off)
		return (ft_omstream_rewind(self, self->cur - off));
	return (ft_omstream_forward(self, off - self->cur));
}

inline size_t	ft_omstream_tell(t_omstream const *self)
{
	return (self->cur);
}
