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

inline ssize_t	ft_putc(int fd, char c)
{
	return (ft_write(fd, (uint8_t *)(&c), sizeof(char)));
}

inline ssize_t	ft_putr(int fd, char c, size_t n)
{
	char buf[(n * sizeof(char)) + 1];

	ft_memset(buf, c, n);
	buf[n] = '\0';
	return (ft_puts(fd, buf));
}
