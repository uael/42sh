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

inline ssize_t	ft_read(int fd, void *buf, size_t sz)
{
	ssize_t		rd;

	while ((rd = read(fd, buf, sz)) < 0)
		if (errno != EINTR && errno != EAGAIN)
			return (THROW(WUT));
	return (rd);
}

inline ssize_t	ft_write(int fd, void const *buf, size_t sz)
{
	ssize_t		wr;

	while ((wr = write(fd, buf, sz)) < 0)
		if (errno != EINTR && errno != EAGAIN)
		{
			if (errno == EBADF && fd == 2)
				exit(EXIT_FAILURE);
			return (THROW(WUT));
		}
	return (wr);
}

inline int		ft_dup2std(int *io, int *src)
{
	if (io[STDIN_FILENO] >= 0 && io[STDIN_FILENO] != src[STDIN_FILENO])
	{
		if (dup2(io[STDIN_FILENO], src[STDIN_FILENO]) < 0 ||
			close(io[STDIN_FILENO]))
			return (THROW(WUT));
	}
	if (io[STDOUT_FILENO] >= 0 && io[STDOUT_FILENO] != src[STDOUT_FILENO])
	{
		if (dup2(io[STDOUT_FILENO], src[STDOUT_FILENO]) < 0 ||
			close(io[STDOUT_FILENO]))
			return (THROW(WUT));
	}
	if (io[STDERR_FILENO] >= 0 && io[STDERR_FILENO] != src[STDERR_FILENO])
	{
		if (dup2(io[STDERR_FILENO], src[STDERR_FILENO]) < 0 ||
			close(io[STDERR_FILENO]))
			return (THROW(WUT));
	}
	return (YEP);
}
