/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:18 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 15:24:15 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline char	*ft_strnstr(char const *haystack, char const *needle, size_t l)
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
