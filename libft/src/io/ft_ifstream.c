/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 17:07:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ifstream.h"

inline void	ft_ofstream_cin(t_ifstream *self)
{
	FT_INIT(self, t_ifstream);
	self->fd = STDIN_FILENO;
}

inline t_st	ft_ifstream_open(t_ifstream *self, char const *filename)
{
	FT_INIT(self, t_ifstream);
	if ((self->fd = open(filename, O_RDONLY)) < 0)
		return (ENO);
	self->filename = filename;
	return (OK);
}

inline t_st	ft_ifstream_close(t_ifstream *self)
{
	if (self->filename && self->fd > 1)
	{
		ft_ifstream_flush(self);
		if (close(self->fd) < 0)
			return (ENO);
		if (self->buf)
		{
			free(self->buf);
			self->buf = NULL;
		}
		self->filename = NULL;
	}
	return (OK);
}
