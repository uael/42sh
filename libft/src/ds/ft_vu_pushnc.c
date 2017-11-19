/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_pushnc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_pushnc(t_vu8 *self, uint8_t const *items, size_t n)
{
	uint8_t *it;

	if (!(it = ft_vu8_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int8_t));
	return (it);
}

inline uint16_t	*ft_vu16_pushnc(t_vu16 *self, uint16_t const *items, size_t n)
{
	uint16_t *it;

	if (!(it = ft_vu16_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int16_t));
	return (it);
}

inline uint32_t	*ft_vu32_pushnc(t_vu32 *self, uint32_t const *items, size_t n)
{
	uint32_t *it;

	if (!(it = ft_vu32_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int32_t));
	return (it);
}

inline uint64_t	*ft_vu64_pushnc(t_vu64 *self, uint64_t const *items, size_t n)
{
	uint64_t *it;

	if (!(it = ft_vu64_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int64_t));
	return (it);
}

inline void		*ft_vec_pushnc(t_vec *self, void const *items, size_t n)
{
	void *it;

	if (!(it = ft_vec_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * self->isz);
	return (it);
}
