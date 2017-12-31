/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_pushc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 18:02:00 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_pushc(t_du8 *self, uint8_t item)
{
	uint8_t *it;

	if (!(it = ft_du8_push(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint16_t	*ft_du16_pushc(t_du16 *self, uint16_t item)
{
	uint16_t *it;

	if (!(it = ft_du16_push(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint32_t	*ft_du32_pushc(t_du32 *self, uint32_t item)
{
	uint32_t *it;

	if (!(it = ft_du32_push(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint64_t	*ft_du64_pushc(t_du64 *self, uint64_t item)
{
	uint64_t *it;

	if (!(it = ft_du64_push(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline void		*ft_deq_pushc(t_deq *self, void *item)
{
	void *it;

	if (!(it = ft_deq_push(self)))
		return (NULL);
	ft_memcpy(it, item, self->isz);
	return (it);
}
