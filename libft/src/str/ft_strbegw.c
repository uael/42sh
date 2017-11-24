/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbegw.c                                       :+:      :+:    :+:   */
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
	while (((uint8_t)*s1 == (uint8_t)*s2) && *s1)
	{
		++s1;
		++s2;
	}
	return (!*s1 ? (char *)s3 : NULL);
}
