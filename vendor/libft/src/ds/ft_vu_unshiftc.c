/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_unshiftc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_unshiftc(t_vu8 *self, uint8_t item)
{
	uint8_t *it;

	if (!(it = ft_vu8_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint16_t	*ft_vu16_unshiftc(t_vu16 *self, uint16_t item)
{
	uint16_t *it;

	if (!(it = ft_vu16_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint32_t	*ft_vu32_unshiftc(t_vu32 *self, uint32_t item)
{
	uint32_t *it;

	if (!(it = ft_vu32_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline uint64_t	*ft_vu64_unshiftc(t_vu64 *self, uint64_t item)
{
	uint64_t *it;

	if (!(it = ft_vu64_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline void		*ft_vec_unshiftc(t_vec *self, void *item)
{
	uint64_t *it;

	if (!(it = ft_vec_unshift(self)))
		return (NULL);
	ft_memcpy(it, item, self->isz);
	return (it);
}
