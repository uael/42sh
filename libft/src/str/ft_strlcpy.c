/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:05 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

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
