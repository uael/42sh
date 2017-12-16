/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_put(t_vu8 *self, size_t idx)
{
	return (ft_vu8_putn(self, idx, 1));
}

inline uint16_t	*ft_vu16_put(t_vu16 *self, size_t idx)
{
	return (ft_vu16_putn(self, idx, 1));
}

inline uint32_t	*ft_vu32_put(t_vu32 *self, size_t idx)
{
	return (ft_vu32_putn(self, idx, 1));
}

inline uint64_t	*ft_vu64_put(t_vu64 *self, size_t idx)
{
	return (ft_vu64_putn(self, idx, 1));
}

inline void		*ft_vec_put(t_vec *self, size_t idx)
{
	return (ft_vec_putn(self, idx, 1));
}
