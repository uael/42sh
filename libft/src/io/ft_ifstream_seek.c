/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream_peek.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ifstream.h"

inline void		ft_ifstream_flush(t_ifstream *self)
{
	(void)self;
	ENO_THROW(WUT, ENIMPL);
}

inline int		ft_ifstream_rewind(t_ifstream *self, size_t n)
{
	(void)self;
	(void)n;
	return (ENO_THROW(WUT, ENIMPL));
}

inline int		ft_ifstream_forward(t_ifstream *self, size_t n)
{
	(void)self;
	(void)n;
	return (ENO_THROW(WUT, ENIMPL));
}

inline int		ft_ifstream_seek(t_ifstream *self, size_t off)
{
	if (!self->filename || self->fd < 0)
		return (ENO_THROW(WUT, EINVAL));
	if (self->cur > off)
		return (ft_ifstream_rewind(self, self->cur - off));
	return (ft_ifstream_forward(self, off - self->cur));
}

inline size_t	ft_ifstream_tell(t_ifstream const *self)
{
	return (self->cur);
}
