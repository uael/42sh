/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cin_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:09:14 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/istream.h"

inline t_sz	ft_cin_read(char *buf, size_t len)
{
	return (ft_istream_read(g_cin, buf, len));
}

t_sz		ft_cin_readf(char *fmt, ...)
{
	va_list	ap;
	t_sz	sz;

	va_start(ap, fmt);
	sz = ft_cin_vreadf(fmt, ap);
	va_end(ap);
	return (sz);
}

inline t_sz	ft_cin_vreadf(char *fmt, va_list ap)
{
	return (ft_istream_vreadf(g_cin, fmt, ap));
}

inline t_sz	ft_cin_get(char *buf, size_t n)
{
	return (ft_istream_get(g_cin, buf, n));
}

inline int	ft_cin_peek(char *c, size_t n)
{
	return (ft_istream_peek(g_cin, c, n));
}
