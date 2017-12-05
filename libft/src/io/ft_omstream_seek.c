/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omstream_peek.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/omstream.h"

inline void		ft_omstream_flush(t_omstream *self)
{
	(void)self;
}

inline t_st		ft_omstream_rewind(t_omstream *self, size_t n)
{
	if (n > self->cur)
		return (ERR(errno = EINVAL));
	self->cur -= n;
	return (OK);
}

inline t_st		ft_omstream_forward(t_omstream *self, size_t n)
{
	if (self->cur + n > self->len)
		return (ERR(errno = EINVAL));
	self->cur += n;
	return (OK);
}

inline t_st		ft_omstream_seek(t_omstream *self, size_t off)
{
	if (self->cur > off)
		return (ft_omstream_rewind(self, self->cur - off));
	return (ft_omstream_forward(self, off - self->cur));
}

inline size_t	ft_omstream_tell(t_omstream const *self)
{
	return (self->cur);
}
