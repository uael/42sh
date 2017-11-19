/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:55 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

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
