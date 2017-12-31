/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_at(t_du8 *self, size_t idx)
{
	return (ft_du8_begin(self) + idx);
}

inline uint16_t	*ft_du16_at(t_du16 *self, size_t idx)
{
	return (ft_du16_begin(self) + idx);
}

inline uint32_t	*ft_du32_at(t_du32 *self, size_t idx)
{
	return (ft_du32_begin(self) + idx);
}

inline uint64_t	*ft_du64_at(t_du64 *self, size_t idx)
{
	return (ft_du64_begin(self) + idx);
}

inline void		*ft_deq_at(t_deq *self, size_t idx)
{
	return ((char *)ft_deq_begin(self) + (idx * self->isz));
}
