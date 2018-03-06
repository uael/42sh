/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

inline ssize_t	ft_puts(int fd, char const *s)
{
	return (ft_write(fd, s, ft_strlen(s)));
}

inline ssize_t	ft_padl(int fd, char const *s, size_t pad)
{
	size_t sz;

	if (!(sz = ft_strlen(s)))
		return (0);
	else if (sz >= pad)
		return (ft_write(fd, s, sz));
	return (ft_write(fd, s, sz) + ft_putr(fd, ' ', (pad - sz) * sizeof(char)));
}

inline ssize_t	ft_padr(int fd, char const *s, size_t pad)
{
	size_t sz;

	if (!(sz = ft_strlen(s)))
		return (0);
	else if (sz >= pad)
		return (ft_write(fd, s, sz));
	return (ft_putr(fd, ' ', (pad - sz) * sizeof(char)) + ft_write(fd, s, sz));
}
