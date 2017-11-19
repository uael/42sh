/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_at(t_vu8 *self, size_t idx)
{
	return (ft_vu8_begin(self) + idx);
}

inline uint16_t	*ft_vu16_at(t_vu16 *self, size_t idx)
{
	return (ft_vu16_begin(self) + idx);
}

inline uint32_t	*ft_vu32_at(t_vu32 *self, size_t idx)
{
	return (ft_vu32_begin(self) + idx);
}

inline uint64_t	*ft_vu64_at(t_vu64 *self, size_t idx)
{
	return (ft_vu64_begin(self) + idx);
}

inline void		*ft_vec_at(t_vec *self, size_t idx)
{
	return ((char *)ft_vec_begin(self) + (idx * self->isz));
}
