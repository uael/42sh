/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libft/math.h"

inline ssize_t	ft_padnl(int fd, int64_t n, uint8_t base, size_t pad)
{
	size_t l;

	if (!(l = ft_intlen(n, base)))
		return (0);
	else if (l >= pad)
		return (ft_putn(fd, n, base));
	return (ft_putn(fd, n, base) + ft_putr(fd, ' ', (pad - l) * sizeof(char)));
}

inline ssize_t	ft_padnr(int fd, int64_t n, uint8_t base, size_t pad)
{
	size_t l;

	if (!(l = ft_intlen(n, base)))
		return (0);
	else if (l >= pad)
		return (ft_putn(fd, n, base));
	return (ft_putr(fd, ' ', (pad - l) * sizeof(char)) + ft_putn(fd, n, base));
}

inline ssize_t	ft_padul(int fd, uint64_t n, uint8_t base, size_t pad)
{
	size_t l;

	if (!(l = ft_intlen(n, base)))
		return (0);
	else if (l >= pad)
		return (ft_putu(fd, n, base));
	return (ft_putu(fd, n, base) + ft_putr(fd, ' ', (pad - l) * sizeof(char)));
}

inline ssize_t	ft_padur(int fd, uint64_t n, uint8_t base, size_t pad)
{
	size_t l;

	if (!(l = ft_intlen(n, base)))
		return (0);
	else if (l >= pad)
		return (ft_putu(fd, n, base));
	return (ft_putr(fd, ' ', (pad - l) * sizeof(char)) + ft_putu(fd, n, base));
}
