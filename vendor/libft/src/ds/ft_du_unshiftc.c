/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_unshiftc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_unshiftc(t_du8 *self, uint8_t item)
{
	uint8_t *it;

	if (!(it = ft_du8_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint16_t	*ft_du16_unshiftc(t_du16 *self, uint16_t item)
{
	uint16_t *it;

	if (!(it = ft_du16_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint32_t	*ft_du32_unshiftc(t_du32 *self, uint32_t item)
{
	uint32_t *it;

	if (!(it = ft_du32_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint64_t	*ft_du64_unshiftc(t_du64 *self, uint64_t item)
{
	uint64_t *it;

	if (!(it = ft_du64_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline void		*ft_deq_unshiftc(t_deq *self, void *item)
{
	uint64_t *it;

	if (!(it = ft_deq_unshift(self)))
		return (NULL);
	ft_memcpy(it, item, self->isz);
	return (it);
}
