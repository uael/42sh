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

inline size_t	ft_strnlen(char const *str, size_t size)
{
	size_t len;

	len = 0;
	while (len < size && *str)
	{
		++len;
		++str;
	}
	return (len);
}

inline char		*ft_strnstr(char const *haystack, char const *needle, size_t l)
{
	char const	*beg;
	char const	*ptr;
	size_t		n;

	if (!*needle)
		return ((char *)haystack);
	while (l-- && *haystack)
	{
		if (*haystack == *needle)
		{
			beg = haystack + 1;
			ptr = needle + 1;
			n = l;
			while (n-- && *ptr == *beg && *ptr)
			{
				++ptr;
				++beg;
			}
			if (!*ptr)
				return ((char *)haystack);
		}
		++haystack;
	}
	return (NULL);
}

inline char		*ft_strrchr(char const *s, int c)
{
	char *beg;

	beg = (char *)s;
	while (*s)
		++s;
	if (c == 0)
		return ((char *)s);
	while (s >= beg)
		if (*s-- == c)
			return ((char *)s + 1);
	return (NULL);
}

inline char		*ft_strstr(char const *haystack, char const *needle)
{
	char const *beg;
	char const *ptr;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			beg = haystack + 1;
			ptr = needle + 1;
			while (*ptr == *beg && *ptr)
			{
				++ptr;
				++beg;
			}
			if (!*ptr)
				return ((char *)haystack);
		}
		++haystack;
	}
	return (NULL);
}

inline size_t	ft_strword(char const *s, char c, char e)
{
	size_t n;

	n = 0;
	while (*s && *s != e)
		if (*s == c)
			++s;
		else if (++n && *++s)
			while (*s && *s != c && *s != e)
				++s;
	return (n);
}
