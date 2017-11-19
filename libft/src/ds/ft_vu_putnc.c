/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_putnc(t_vu8 *self, size_t i, uint8_t const *b, size_t n)
{
	uint8_t *it;

	if (!(it = ft_vu8_putn(self, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int8_t));
	return (it);
}

inline uint16_t	*ft_vu16_putnc(t_vu16 *s, size_t i, uint16_t const *b, size_t n)
{
	uint16_t *it;

	if (!(it = ft_vu16_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int16_t));
	return (it);
}

inline uint32_t	*ft_vu32_putnc(t_vu32 *s, size_t i, uint32_t const *b, size_t n)
{
	uint32_t *it;

	if (!(it = ft_vu32_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int32_t));
	return (it);
}

inline uint64_t	*ft_vu64_putnc(t_vu64 *s, size_t i, uint64_t const *b, size_t n)
{
	uint64_t *it;

	if (!(it = ft_vu64_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int64_t));
	return (it);
}

inline void		*ft_vec_putnc(t_vec *s, size_t i, void const *b, size_t n)
{
	uint64_t *it;

	if (!(it = ft_vec_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * s->isz);
	return (it);
}
