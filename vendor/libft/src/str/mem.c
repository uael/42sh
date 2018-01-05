/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:14 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:29:11 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline void	ft_bzero(void *ptr, size_t n)
{
	uint8_t *str;

	str = (uint8_t *)ptr;
	while (n--)
		*str++ = '\0';
}

inline void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	while (n--)
		if ((*(uint8_t *)dst++ = *(uint8_t *)src++) == (uint8_t)c)
			return (dst);
	return (NULL);
}

inline void	*ft_memchr(void const *ptr, int c, size_t n)
{
	while (n--)
		if (*(uint8_t*)ptr++ == (uint8_t)c)
			return ((void *)ptr - 1);
	return (NULL);
}

inline int	ft_memcmp(void const *s1, void const *s2, size_t n)
{
	uint8_t const	*a;
	uint8_t const	*b;

	a = (uint8_t const *)s1;
	b = (uint8_t const *)s2;
	while (n && *a == *b)
	{
		++a;
		++b;
		--n;
	}
	return (n == 0 ? 0 : *a - *b);
}

inline void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	void *d;

	d = dst;
	while (n)
	{
		*(uint8_t *)dst++ = *(uint8_t const *)src++;
		--n;
	}
	return (d);
}
