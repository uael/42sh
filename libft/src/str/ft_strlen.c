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

inline size_t	ft_strlen(char const *str)
{
	size_t len;

	len = 0;
	while (*str++)
		++len;
	return (len);
}

inline size_t	ft_strlcpy(char *dst, char const *src, size_t size)
{
	char const	*sptr;
	size_t		slen;

	sptr = src;
	while (*sptr++)
		;
	slen = ((size_t)(sptr - src - 1));
	if (slen < size)
		ft_strncpy(dst, src, slen + 1);
	else if (size != 0)
	{
		ft_strncpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (slen);
}

inline size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	size_t slen;
	size_t dlen;

	slen = ft_strlen(src);
	dlen = ft_strnlen(dest, size);
	if (dlen == size)
		return (size + slen);
	if (slen < size - dlen)
		ft_strncpy(dest + dlen, src, slen + 1);
	else
	{
		ft_strncpy(dest + dlen, src, size - dlen - 1);
		dest[size - 1] = '\0';
	}
	return (dlen + slen);
}
