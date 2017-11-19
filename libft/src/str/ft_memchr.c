/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:48 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:49:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline void	*ft_memchr(void const *ptr, int c, size_t n)
{
	while (n--)
		if (*(uint8_t*)ptr++ == (uint8_t)c)
			return ((void *)ptr - 1);
	return (NULL);
}
