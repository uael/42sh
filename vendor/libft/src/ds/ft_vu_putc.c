/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_putc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_putc(t_vu8 *self, size_t idx, uint8_t item)
{
	uint8_t *it;

	if (!(it = ft_vu8_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint16_t	*ft_vu16_putc(t_vu16 *self, size_t idx, uint16_t item)
{
	uint16_t *it;

	if (!(it = ft_vu16_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint32_t	*ft_vu32_putc(t_vu32 *self, size_t idx, uint32_t item)
{
	uint32_t *it;

	if (!(it = ft_vu32_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint64_t	*ft_vu64_putc(t_vu64 *self, size_t idx, uint64_t item)
{
	uint64_t *it;

	if (!(it = ft_vu64_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline void		*ft_vec_putc(t_vec *self, size_t idx, void *item)
{
	void *it;

	if (!(it = ft_vec_put(self, idx)))
		return (NULL);
	ft_memcpy(it, item, self->isz);
	return (it);
}
