/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imstream_peek.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/imstream.h"

inline void		ft_imstream_flush(t_imstream *self)
{
	(void)self;
}

inline t_ret	ft_imstream_rewind(t_imstream *self, size_t n)
{
	(void)self;
	(void)n;
	return (RET_ERR);
}

inline t_ret	ft_imstream_forward(t_imstream *self, size_t n)
{
	(void)self;
	(void)n;
	return (RET_ERR);
}

inline t_ret	ft_imstream_seek(t_imstream *self, size_t off)
{
	if (self->cur > off)
		return (ft_imstream_rewind(self, self->cur - off));
	return (ft_imstream_forward(self, off - self->cur));
}

inline size_t	ft_imstream_tell(t_imstream const *self)
{
	return (self->cur);
}
