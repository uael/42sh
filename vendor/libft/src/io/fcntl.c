/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcntl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

extern ssize_t	ft_read(int fd, void *buf, size_t sz)
{
	ssize_t		rd;

	while ((rd = read(fd, buf, sz)) < 0)
		if (errno != EINTR && errno != EAGAIN)
			return (THROW(WUT));
	return (rd);
}

extern ssize_t	ft_write(int fd, void const *buf, size_t sz)
{
	ssize_t		wr;

	while ((wr = write(fd, buf, sz)) < 0)
		if (errno != EINTR && errno != EAGAIN)
			return (THROW(WUT));
	return (wr);
}
