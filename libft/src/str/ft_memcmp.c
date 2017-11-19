/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:50 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:24:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline int	ft_memcmp(void const *s1, void const *s2, size_t n)
{
	uint8_t const	*a;
	uint8_t const	*b;

	a = (uint8_t const *)s1;
	b = (uint8_t const *)s2;
	while (n && *a == *b)
	{
		++a;
		++b;
		--n;
	}
	return (n == 0 ? 0 : *a - *b);
}
