/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_unshiftnc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_unshiftnc(t_du8 *self, uint8_t const *items, size_t n)
{
	uint8_t *it;

	if (!(it = ft_du8_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int8_t));
	return (it);
}

inline uint16_t	*ft_du16_unshiftnc(t_du16 *self, uint16_t const *b, size_t n)
{
	uint16_t *it;

	if (!(it = ft_du16_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int16_t));
	return (it);
}

inline uint32_t	*ft_du32_unshiftnc(t_du32 *self, uint32_t const *b, size_t n)
{
	uint32_t *it;

	if (!(it = ft_du32_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int32_t));
	return (it);
}

inline uint64_t	*ft_du64_unshiftnc(t_du64 *self, uint64_t const *b, size_t n)
{
	uint64_t *it;

	if (!(it = ft_du64_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int64_t));
	return (it);
}

inline void		*ft_deq_unshiftnc(t_deq *self, void const *b, size_t n)
{
	void *it;

	if (!(it = ft_deq_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, b, n * self->isz);
	return (it);
}
