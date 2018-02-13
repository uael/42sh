/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline char	*ft_strnchr(char const *s, int c, size_t n)
{
	if (c == 0)
		while (n--)
			if (!*s++)
				return ((char *)s - 1);
	if (c == 0)
		return (NULL);
	while (n-- && *s)
		if (*s++ == c)
			return ((char *)s - 1);
	return (NULL);
}

inline char	*ft_strscpy(char **dst, size_t *n, char *src)
{
	while (*src && *n)
	{
		*(*dst)++ = *src++;
		--*n;
	}
	if (!*src)
		return (NULL);
	return (src);
}

inline char	*ft_strendw(char const *s1, char const *s2)
{
	char const *s3;
	char const *s4;

	s3 = s1;
	s4 = s2;
	while (*s1)
		++s1;
	while (*s2)
		++s2;
	while ((*(uint8_t *)s1 == *(uint8_t *)s2) && s1 > s3 && s2 > s4)
	{
		--s1;
		--s2;
	}
	return (s2 == s4 ? (char *)s3 : NULL);
}

inline char	*ft_strndup(char const *src, size_t n)
{
	char	*dup;

	dup = ft_malloc((n + 1) * sizeof(char));
	ft_memcpy(dup, src, n);
	dup[n] = '\0';
	return (dup);
}

inline char	*ft_strrschr(char const *beg, char const *end, char c)
{
	while (end > beg)
		if (*end == c)
			return ((char *)end);
		else
			--end;
	return (NULL);
}
