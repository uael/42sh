/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:05:03 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"
#include "libft/int.h"

inline uint8_t	ft_strnbr(char *dst, int64_t n, uint8_t base)
{
	uint8_t		i;
	uint8_t		mod;
	static char	digits[31] = "0123456789abcdefghijklmnopqrst";

	if (base > 30)
		return (0);
	i = ft_intlen(n, base);
	mod = (uint8_t)(n < 0);
	if (mod)
		*dst++ = '-';
	dst += i - 1;
	if (n == 0)
		*dst-- = '0';
	while (n)
	{
		*dst-- = digits[(n % base) * (mod ? -1 : 1)];
		n /= base;
	}
	return (i + mod);
}
