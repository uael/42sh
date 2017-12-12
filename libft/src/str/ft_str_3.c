/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"
#include "libft/int.h"

inline size_t	ft_strlen(char const *str)
{
	size_t len;

	len = 0;
	while (*str++)
		++len;
	return (len);
}

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

inline char		*ft_strncat(char *dest, char const *src, size_t nb)
{
	char *ptr;

	ptr = dest;
	while (*ptr)
		++ptr;
	while (nb && (*ptr++ = *src++))
		--nb;
	if (nb <= 0)
		*ptr = '\0';
	return (dest);
}

inline int		ft_strncmp(char const *s1, char const *s2, size_t n)
{
	while (n && ((uint8_t)*s1 == (uint8_t)*s2) && *s1)
	{
		++s1;
		++s2;
		--n;
	}
	return (n == 0 ? 0 : *(uint8_t *)s1 - *(uint8_t *)s2);
}

inline char		*ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i])
	{
		*(dest + i) = *(src + i);
		++i;
	}
	while (i < n)
		*(dest + i++) = '\0';
	return (dest);
}
