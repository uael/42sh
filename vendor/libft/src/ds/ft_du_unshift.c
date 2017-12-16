/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_unshiftn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:31:14 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_unshift(t_du8 *self)
{
	return (ft_du8_unshiftn(self, 1));
}

inline uint16_t	*ft_du16_unshift(t_du16 *self)
{
	return (ft_du16_unshiftn(self, 1));
}

inline uint32_t	*ft_du32_unshift(t_du32 *self)
{
	return (ft_du32_unshiftn(self, 1));
}

inline uint64_t	*ft_du64_unshift(t_du64 *self)
{
	return (ft_du64_unshiftn(self, 1));
}

inline void		*ft_deq_unshift(t_deq *self)
{
	return (ft_deq_unshiftn(self, 1));
}
