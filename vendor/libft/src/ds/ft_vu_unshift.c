/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_unshiftn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_unshift(t_vu8 *self)
{
	return (ft_vu8_unshiftn(self, 1));
}

inline uint16_t	*ft_vu16_unshift(t_vu16 *self)
{
	return (ft_vu16_unshiftn(self, 1));
}

inline uint32_t	*ft_vu32_unshift(t_vu32 *self)
{
	return (ft_vu32_unshiftn(self, 1));
}

inline uint64_t	*ft_vu64_unshift(t_vu64 *self)
{
	return (ft_vu64_unshiftn(self, 1));
}

inline void		*ft_vec_unshift(t_vec *self)
{
	return (ft_vec_unshiftn(self, 1));
}
