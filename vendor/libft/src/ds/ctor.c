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
	ft_bzero(self, sizeof(t_deq));
	self->isz = isz;
}

inline void		ft_mapctor(t_map *map, t_hasher hasher, size_t ksz, size_t vsz)
{
	ft_bzero(map, sizeof(t_map));
	map->hasher = hasher;
	map->ksz = ksz;
	map->vsz = vsz;
}

inline void		ft_sdsctor(t_sds *self)
{
	ft_bzero(self, sizeof(t_sds));
}

inline void		ft_setctor(t_set *set, t_hasher hasher, size_t ksz)
{
	ft_bzero(set, sizeof(t_set));
	set->hasher = hasher;
	set->ksz = ksz;
}

inline void		ft_vecctor(t_vec *self, size_t isz)
{
	ft_bzero(self, sizeof(t_vec));
	self->isz = isz;
}
