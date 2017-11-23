/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_putc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_putc(t_du8 *self, size_t idx, uint8_t item)
{
	uint8_t *it;

	if (!(it = ft_du8_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint16_t	*ft_du16_putc(t_du16 *self, size_t idx, uint16_t item)
{
	uint16_t *it;

	if (!(it = ft_du16_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint32_t	*ft_du32_putc(t_du32 *self, size_t idx, uint32_t item)
{
	uint32_t *it;

	if (!(it = ft_du32_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint64_t	*ft_du64_putc(t_du64 *self, size_t idx, uint64_t item)
{
	uint64_t *it;

	if (!(it = ft_du64_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline void		*ft_deq_putc(t_deq *self, size_t idx, void *item)
{
	void *it;

	if (!(it = ft_deq_put(self, idx)))
		return (NULL);
	ft_memcpy(it, item, self->isz);
	return (it);
}
