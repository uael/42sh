/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:02:13 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

void			ft_ofsctor(t_ofs *self, int ofd)
{
	self->ofd = ofd;
	self->i = 0;
}

int				ft_ofsopen(t_ofs *self, char const *filename)
{
	int fd;

	if ((fd = open(filename, O_WRONLY, S_IRUSR | S_IWUSR)) < 0)
		return (WUT);
	ft_ofsctor(self, fd);
	return (YEP);
}

int				ft_ofsclose(t_ofs *self)
{
	ft_ofsflush(self);
	if (close(self->ofd))
		return (WUT);
	return (YEP);
}

inline ssize_t	ft_ofsflush(t_ofs *self)
{
	ssize_t sz;

	if (!self->i)
		return (0);
	sz = ft_write(self->ofd, self->buf, self->i);
	self->i = 0;
	return (sz);
}

inline ssize_t	ft_ofswrc(t_ofs *self, unsigned char c)
{
	self->buf[self->i++] = c;
	if (self->i == FT_PAGE_SIZE && ft_ofsflush(self) < 0)
		return (WUT);
	return (YEP);
}
