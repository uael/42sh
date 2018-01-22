/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

#define BSZ FT_PAGE_SIZE

inline void				ft_ifsctor(t_ifs *self, int ifd)
{
	self->ifd = ifd;
	self->i = 0;
	self->rd = 0;
	self->buf = NULL;
}

inline void				ft_ifsdtor(t_ifs *self)
{
	if (self->buf)
		free(self->buf);
	FT_INIT(self, t_ifs);
}

inline int				ft_ifsopen(t_ifs *self, char const *filename)
{
	int	fd;

	if ((fd = open(filename, O_RDONLY, S_IRUSR | S_IWUSR)) < 0)
		return (WUT);
	ft_ifsctor(self, fd);
	return (YEP);
}

inline int				ft_ifsclose(t_ifs *self)
{
	int fd;

	fd = self->ifd;
	ft_ifsdtor(self);
	if (close(fd))
		return (WUT);
	return (YEP);
}

inline char				ft_ifspeek(t_ifs *self, size_t i)
{
	char	*buf;
	ssize_t	sz;

	buf = NULL;
	if ((sz = ft_ifsbuf(self, i, &buf)) <= 0)
		return ((char)(sz < 0 ? WUT : '\0'));
	return (buf[i]);
}
