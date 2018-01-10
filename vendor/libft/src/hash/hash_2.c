/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 09:54:36 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/hash.h"

inline uint32_t	ft_ullhash(unsigned long long int ull)
{
	return (LLHASH(ull));
}

inline uint32_t	ft_szhash(ssize_t sz)
{
	return (SZHASH(sz));
}

inline uint32_t	ft_uszhash(ssize_t usz)
{
	return (SZHASH(usz));
}

inline uint32_t	ft_strhash(char const *str)
{
	uint32_t h;

	if ((h = (uint32_t)*str))
		while (*++str)
			h = (h << 5) - h + (uint32_t)*str;
	return (h);
}
