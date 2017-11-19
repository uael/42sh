/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_ctor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline void	ft_vu8_ctor(t_vu8 *self)
{
	FT_INIT(self, t_vu8);
}

inline void	ft_vu16_ctor(t_vu16 *self)
{
	FT_INIT(self, t_vu16);
}

inline void	ft_vu32_ctor(t_vu32 *self)
{
	FT_INIT(self, t_vu16);
}

inline void	ft_vu64_ctor(t_vu64 *self)
{
	FT_INIT(self, t_vu64);
}

inline void	ft_vec_ctor(t_vec *self, size_t isz)
{
	FT_INIT(self, t_vu64);
	self->isz = isz;
}
