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
#include "libft/math.h"

inline ssize_t	ft_puts(int fd, char const *s)
{
	return (write(fd, s, ft_strlen(s)));
}

inline ssize_t	ft_padl(int fd, char const *s, size_t pad)
{
	size_t len;

	if (!(len = ft_strlen(s)))
		return (0);
	else if (len >= pad)
		return (write(fd, s, len));
	return (write(fd, s, len) + ft_putr(fd, ' ', (pad - len) * sizeof(char)));
}

inline ssize_t	ft_padr(int fd, char const *s, size_t pad)
{
	size_t len;

	if (!(len = ft_strlen(s)))
		return (0);
	else if (len >= pad)
		return (write(fd, s, len));
	return (ft_putr(fd, ' ', (pad - len) * sizeof(char)) + write(fd, s, len));
}
