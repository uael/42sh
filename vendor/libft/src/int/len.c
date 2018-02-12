/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/int.h"

inline uint8_t	ft_floatlen(float n, int precision, uint8_t base)
{
	uint8_t	i;
	float	d;

	if ((int64_t)n == n)
		return (ft_intlen((int64_t)n, base));
	i = ft_intlen((int64_t)n, base);
	d = n - (int64_t)n;
	return (i + ft_intlen((int64_t)(precision * d), 10));
}

inline uint8_t	ft_intlen(int64_t n, uint8_t base)
{
	uint8_t	i;

	i = 1;
	while (n /= base)
		++i;
	return (i);
}

inline uint8_t	ft_uintlen(uint64_t n, uint8_t base)
{
	uint8_t	i;

	i = 1;
	while (n /= base)
		++i;
	return (i);
}
