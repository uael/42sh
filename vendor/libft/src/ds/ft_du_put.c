/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_put(t_du8 *self, size_t idx)
{
	return (ft_du8_putn(self, idx, 1));
}

inline uint16_t	*ft_du16_put(t_du16 *self, size_t idx)
{
	return (ft_du16_putn(self, idx, 1));
}

inline uint32_t	*ft_du32_put(t_du32 *self, size_t idx)
{
	return (ft_du32_putn(self, idx, 1));
}

inline uint64_t	*ft_du64_put(t_du64 *self, size_t idx)
{
	return (ft_du64_putn(self, idx, 1));
}

inline void		*ft_deq_put(t_deq *self, size_t idx)
{
	return (ft_deq_putn(self, idx, 1));
}
