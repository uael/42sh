/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:56:04 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/int.h"

inline uint8_t	ft_floatstr(char *dst, double n, int precision, uint8_t base)
{
	uint8_t	l;
	float	d;
	float	di;

	if ((int64_t)n == n)
		return (ft_intstr(dst, (int64_t)n, base));
	d = n - (int64_t)n;
	if (d >= 0.95)
		d = ((int)++n & 0);
	l = ft_intstr(dst, (int64_t)n, base);
	dst[l++] = '.';
	di = precision * d;
	return (l + ft_intstr(dst + l,
		(int64_t)di + ((di - (int64_t)di) >= 0.5 ? 1 : 0), base));
}

inline uint8_t	ft_intstr(char *dst, int64_t n, uint8_t base)
{
	uint8_t		i;
	static char	digits[31] = "0123456789abcdefghijklmnopqrst";

	if (n >= 0)
		return (ft_uintstr(dst, (uint64_t)n, base));
	if (base > 30)
		return (0);
	i = ft_intlen(n, base);
	*dst++ = '-';
	dst += i - 1;
	while (n)
	{
		*dst-- = digits[-(n % base)];
		n /= base;
	}
	return ((uint8_t)(i + 1));
}

inline uint8_t	ft_uintstr(char *dst, uint64_t n, uint8_t base)
{
	uint8_t		i;
	static char	digits[31] = "0123456789abcdefghijklmnopqrst";

	if (base > 30)
		return (0);
	if (n == 0)
		return ((uint8_t)(((*dst = '0') & 0) + 1));
	i = ft_intlen(n, base);
	dst += i - 1;
	while (n)
	{
		*dst-- = digits[n % base];
		n /= base;
	}
	return (i);
}
