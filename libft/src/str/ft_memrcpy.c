/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:17 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/09 12:20:15 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline void	*ft_memrcpy(void *dst, void const *src, size_t n)
{
	while (n--)
		*((uint8_t *)dst + n) = *((uint8_t const *)src + n);
	return (dst);
}
