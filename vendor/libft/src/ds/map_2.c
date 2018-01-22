/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

t_bool					ft_mapget(t_map *self, void *key, uint32_t *out)
{
	uint32_t	i;
	uint32_t	last;
	uint32_t	mask;
	uint32_t	step;

	if (!self->cap)
		return (0);
	step = 0;
	mask = self->cap - 1;
	i = self->hasher.hash(key) & mask;
	last = i;
	while (!BUCKET_ISEMPTY(self->bucks, i) && (BUCKET_ISDEL(self->bucks, i) || !
		self->hasher.eq(*(void **)((char *)self->keys + (i * self->ksz)), key)))
	{
		i = (i + (++step)) & mask;
		if (i == last)
			return (0);
	}
	if (BUCKET_ISEITHER(self->bucks, i))
		return (0);
	if (out)
		*out = i;
	return (1);
}

static inline uint32_t	mapput(t_map *self, void *key)
{
	uint32_t i;
	uint32_t last;
	uint32_t mask;
	uint32_t step;

	step = 0;
	if (self->occupieds >= self->upper_bound)
		ft_maprsz(self, self->cap > (self->len << 1)
			? self->cap - 1 : self->cap + 1);
	mask = self->cap - 1;
	i = self->hasher.hash(key) & mask;
	last = i;
	while (1)
		if (self->bucks[i] & BUCKET_EMPTY || (!(self->bucks[i] &
			BUCKET_DELETED) && self->hasher.eq(*(void **)((char *)self->keys +
			(i * self->ksz)), key)))
			break ;
		else if ((i = (i + (++step)) & mask) == last)
			break ;
	return (i);
}

t_bool					ft_mapput(t_map *self, void *key, uint32_t *out)
{
	uint32_t x;

	x = mapput(self, key);
	if (out)
		*out = x;
	if (BUCKET_ISEMPTY(self->bucks, x))
	{
		*(void **)((char *)self->keys + (x * self->ksz)) = key;
		BUCKET_SET_ISBOTH_FALSE(self->bucks, x);
		++self->len;
		++self->occupieds;
		return (1);
	}
	else if (BUCKET_ISDEL(self->bucks, x))
	{
		*(void **)((char *)self->keys + (x * self->ksz)) = key;
		BUCKET_SET_ISBOTH_FALSE(self->bucks, x);
		++self->len;
		return (1);
	}
	return (0);
}

t_bool					ft_mapdel(t_map *map, uint32_t it)
{
	if (it != map->cap && BUCKET_ISPOPULATED(map->bucks, it))
	{
		BUCKET_SET_ISDEL_TRUE(map->bucks, it);
		--map->len;
		return (1);
	}
	return (0);
}
