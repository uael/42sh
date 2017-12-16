/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_push(t_du8 *self)
{
	return (ft_du8_pushn(self, 1));
}

inline uint16_t	*ft_du16_push(t_du16 *self)
{
	return (ft_du16_pushn(self, 1));
}

inline uint32_t	*ft_du32_push(t_du32 *self)
{
	return (ft_du32_pushn(self, 1));
}

inline uint64_t	*ft_du64_push(t_du64 *self)
{
	return (ft_du64_pushn(self, 1));
}

inline void		*ft_deq_push(t_deq *self)
{
	return (ft_deq_pushn(self, 1));
}
