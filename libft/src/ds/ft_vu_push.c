/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_push(t_vu8 *self)
{
	return (ft_vu8_pushn(self, 1));
}

inline uint16_t	*ft_vu16_push(t_vu16 *self)
{
	return (ft_vu16_pushn(self, 1));
}

inline uint32_t	*ft_vu32_push(t_vu32 *self)
{
	return (ft_vu32_pushn(self, 1));
}

inline uint64_t	*ft_vu64_push(t_vu64 *self)
{
	return (ft_vu64_pushn(self, 1));
}

inline void		*ft_vec_push(t_vec *self)
{
	return (ft_vec_pushn(self, 1));
}
