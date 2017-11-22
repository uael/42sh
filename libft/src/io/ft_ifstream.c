/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ifstream.h"

inline t_ret	ft_ifstream_open(t_ifstream *self, char const *filename)
{
	FT_INIT(self, t_ifstream);
	if ((self->fd = open(filename, O_RDONLY)) < 0)
		return (RET_ERR);
	self->filename = filename;
	return (RET_OK);
}

inline t_ret	ft_ifstream_close(t_ifstream *self)
{
	if (self->filename && self->fd > 1)
	{
		ft_ifstream_flush(self);
		if (close(self->fd) < 0)
			return (RET_ERR);
		if (self->buf)
		{
			free(self->buf);
			self->buf = NULL;
		}
		self->filename = NULL;
	}
	return (RET_OK);
}
