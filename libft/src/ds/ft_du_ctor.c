/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_ctor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline void	ft_du8_ctor(t_du8 *self)
{
	FT_INIT(self, t_du8);
}

inline void	ft_du16_ctor(t_du16 *self)
{
	FT_INIT(self, t_du16);
}

inline void	ft_du32_ctor(t_du32 *self)
{
	FT_INIT(self, t_du16);
}

inline void	ft_du64_ctor(t_du64 *self)
{
	FT_INIT(self, t_du64);
}

inline void	ft_deq_ctor(t_deq *self, size_t isz)
{
	FT_INIT(self, t_du64);
	self->isz = isz;
}
