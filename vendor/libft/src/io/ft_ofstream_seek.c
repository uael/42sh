/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ofstream_peek.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libft/io/ofstream.h"

inline void		ft_ofstream_flush(t_ofstream *self)
{
	ssize_t	sz;

	if ((sz = ft_write(self->fd, self->buf, self->len)) >= 0)
	{
		self->beg += sz;
		self->len = 0;
	}
}

inline int		ft_ofstream_rewind(t_ofstream *self, size_t n)
{
	(void)self;
	(void)n;
	return (ENO_THROW(WUT, ENIMPL));
}

inline int		ft_ofstream_forward(t_ofstream *self, size_t n)
{
	(void)self;
	(void)n;
	return (ENO_THROW(WUT, ENIMPL));
}

inline int		ft_ofstream_seek(t_ofstream *self, size_t off)
{
	if (!self->filename || self->fd < 0)
		return (ENO_THROW(WUT, EINVAL));
	if (self->cur > off)
		return (ft_ofstream_rewind(self, self->cur - off));
	return (ft_ofstream_forward(self, off - self->cur));
}

inline size_t	ft_ofstream_tell(t_ofstream const *self)
{
	return (self->cur);
}
