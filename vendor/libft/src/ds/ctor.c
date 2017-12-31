/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void		ft_deqctor(t_deq *self, size_t isz)
{
	FT_INIT(self, t_deq);
	self->isz = isz;
}

inline void		ft_sdsctor(t_sds *self)
{
	FT_INIT(self, t_sds);
}

inline void		ft_vecctor(t_vec *self, size_t isz)
{
	FT_INIT(self, t_vec);
	self->isz = isz;
}
