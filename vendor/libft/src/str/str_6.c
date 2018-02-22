/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline size_t	ft_strcspn(const char *s1, const char *s2)
{
	size_t ret;

	ret = 0;
	while (*s1)
		if (ft_strchr(s2, *s1))
			return (ret);
		else
		{
			++s1;
			++ret;
		}
	return (ret);
}

inline char		*ft_stpcpy(char *dest, char const *src)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	*d++ = *s;
	while (*s++ != '\0')
		*d++ = *s;
	return (d - 1);
}

inline size_t	ft_strspn(const char *s, const char *accept)
{
	const char	*p;
	const char	*a;
	size_t		c;

	c = 0;
	p = s - 1;
	while (*++p)
	{
		a = accept - 1;
		while (*++a)
			if (*p == *a)
				break ;
		if (*a == '\0')
			return (c);
		else
			++c;
	}
	return (c);
}

inline char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;

	s = (char *)ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	while (*s1)
		s[i++] = *s1++;
	while (*s2)
		s[i++] = *s2++;
	s[i] = '\0';
	return (s);
}
