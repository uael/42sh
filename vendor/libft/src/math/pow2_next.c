/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow2_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 17:16:54 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"

inline uint8_t	pow2_next8(uint8_t n)
{
	uint32_t j;
	uint32_t i;

	if (n == UINT8_MAX || ISPOW2(n))
		return (n);
	i = (uint32_t)n;
	if (!(j = i & 0xFFFF0000))
		j = i;
	if (!(i = j & 0xFF00FF00))
		i = j;
	if (!(j = i & 0xF0F0F0F0))
		j = i;
	if (!(i = j & 0xCCCCCCCC))
		i = j;
	if (!(j = i & 0xAAAAAAAA))
		j = i;
	i = j << 1;
	return ((i > UINT8_MAX || i < n) ? (uint8_t)UINT8_MAX : (uint8_t)i);
}

inline uint16_t	pow2_next16(uint16_t n)
{
	uint32_t j;
	uint32_t i;

	if (n == UINT16_MAX || ISPOW2(n))
		return (n);
	i = (uint32_t)n;
	if (!(j = i & 0xFFFF0000))
		j = i;
	if (!(i = j & 0xFF00FF00))
		i = j;
	if (!(j = i & 0xF0F0F0F0))
		j = i;
	if (!(i = j & 0xCCCCCCCC))
		i = j;
	if (!(j = i & 0xAAAAAAAA))
		j = i;
	i = j << 1;
	return ((i > UINT16_MAX || i < n) ? (uint16_t)UINT16_MAX : (uint16_t)i);
}

inline uint32_t	pow2_next32(uint32_t n)
{
	uint32_t j;
	uint32_t i;

	if (n == UINT32_MAX || ISPOW2(n))
		return (n);
	i = n;
	if (!(j = i & 0xFFFF0000))
		j = i;
	if (!(i = j & 0xFF00FF00))
		i = j;
	if (!(j = i & 0xF0F0F0F0))
		j = i;
	if (!(i = j & 0xCCCCCCCC))
		i = j;
	if (!(j = i & 0xAAAAAAAA))
		j = i;
	i = j << 1;
	return ((i > UINT32_MAX || i < n) ? (uint32_t)UINT32_MAX : (uint32_t)i);
}

inline uint64_t	pow2_next64(uint64_t n)
{
	uint64_t j;
	uint64_t i;

	if (n == UINT64_MAX || ISPOW2(n))
		return (n);
	i = n;
	if (!(j = i & 0xFFFF0000))
		j = i;
	if (!(i = j & 0xFF00FF00))
		i = j;
	if (!(j = i & 0xF0F0F0F0))
		j = i;
	if (!(i = j & 0xCCCCCCCC))
		i = j;
	if (!(j = i & 0xAAAAAAAA))
		j = i;
	i = j << 1;
	return ((i > UINT64_MAX || i < n) ? (uint64_t)UINT64_MAX : (uint64_t)i);
}

inline size_t	pow2_next(size_t n)
{
	size_t i;
	size_t j;

	if (n == SIZE_MAX || ISPOW2(n))
		return (n);
	i = (uint32_t)n;
	if (!(j = i & 0xFFFF0000))
		j = i;
	if (!(i = j & 0xFF00FF00))
		i = j;
	if (!(j = i & 0xF0F0F0F0))
		j = i;
	if (!(i = j & 0xCCCCCCCC))
		i = j;
	if (!(j = i & 0xAAAAAAAA))
		j = i;
	i = j << 1;
	return ((i < n) ? (size_t)SIZE_MAX : i);
}
