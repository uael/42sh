/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 16:21:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ifstream.h"
#include "libft/ex.h"
#include "libft/ds.h"

inline void	ft_ofstream_cin(t_ifstream *self)
{
	FT_INIT(self, t_ifstream);
	self->fd = STDIN_FILENO;
}

inline int	ft_ifstream_open(t_ifstream *self, char const *filename)
{
	FT_INIT(self, t_ifstream);
	if ((self->fd = open(filename, O_RDONLY)) < 0)
		return (THROW(WUT));
	self->filename = filename;
	return (YEP);
}

inline int	ft_ifstream_close(t_ifstream *self)
{
	if (self->filename && self->fd > 1)
	{
		ft_ifstream_flush(self);
		if (close(self->fd))
			return (THROW(WUT));
		if (self->buf)
		{
			free(self->buf);
			self->buf = NULL;
		}
		self->filename = NULL;
	}
	return (YEP);
}

char		*ft_ifstream_getl(t_ifstream *self, char sep)
{
	ssize_t	st;
	char	p;
	t_dstr	r;

	p = 0;
	ft_dstr_ctor(&r);
	while ((st = ft_ifstream_read(self, &p, 1)) == 1 && p)
	{
		ft_dstr_pushc(&r, p);
		if (p == sep)
			break ;
	}
	if (st < 0)
	{
		THROW(WUT);
		ft_dstr_dtor(&r, NULL);
		return (NULL);
	}
	return (r.buf);
}
