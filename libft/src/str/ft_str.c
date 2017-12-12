/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:23 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 12:30:38 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline char	*ft_strbegw(char const *s1, char const *s2)
{
	char const *s3;

	s3 = s2;
	while ((*(uint8_t *)s1 == *(uint8_t *)s2) && *s1)
	{
		++s1;
		++s2;
	}
	return (!*s1 ? (char *)s3 : NULL);
}

inline char	*ft_strcat(char *dest, char const *src)
{
	char *ptr;

	ptr = dest;
	while (*ptr)
		++ptr;
	while ((*ptr++ = *src++))
		;
	return (dest);
}

inline char	*ft_strchr(char const *s, int c)
{
	if (c == 0)
		while (1)
			if (!*s++)
				return ((char *)s - 1);
	while (*s)
		if (*s++ == c)
			return ((char *)s - 1);
	return (NULL);
}

inline char	*ft_strmchr(char const *s, char const *c)
{
	while (*s)
		if (ft_strchr(c, *s++))
			return ((char *)s - 1);
	return (NULL);
}

inline void	ft_strclr(char *s)
{
	if (s)
		while (*s)
			*s++ = '\0';
}
