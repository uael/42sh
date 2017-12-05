/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cout_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:09:14 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ostream.h"

inline t_sz	ft_cout_write(char const *buf, size_t len)
{
	return (ft_ostream_write(g_cout, buf, len));
}

t_sz		ft_cout_writef(char const *fmt, ...)
{
	va_list	ap;
	t_sz	sz;

	va_start(ap, fmt);
	sz = ft_cout_vwritef(fmt, ap);
	va_end(ap);
	return (sz);
}

inline t_sz	ft_cout_vwritef(char const *fmt, va_list ap)
{
	return (ft_ostream_vwritef(g_cout, fmt, ap));
}

inline t_sz	ft_cout_putc(char c)
{
	return (ft_ostream_putc(g_cout, c));
}

inline t_sz	ft_cout_puts(char const *s)
{
	return (ft_ostream_puts(g_cout, s));
}
