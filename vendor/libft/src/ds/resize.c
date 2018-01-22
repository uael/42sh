/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

static inline char	hswap(t_map *self, void **key, void **val, uint32_t i)
{
	void			*tmp;

	if (i < self->cap && !BUCKET_ISEITHER(self->bucks, i))
	{
		tmp = *(void **)((char *)self->keys + (i * self->ksz));
		*(void **)((char *)self->keys + (i * self->ksz)) = *key;
		*key = tmp;
		tmp = *(void **)((char *)self->vals + (i * self->vsz));
		*(void **)((char *)self->vals + (i * self->vsz)) = *val;
		*val = tmp;
		BUCKET_SET_ISDEL_TRUE(self->bucks, i);
	}
	else
	{
		*(void **)((char *)self->keys + (i * self->ksz)) = *key;
		*(void **)((char *)self->vals + (i * self->vsz)) = *val;
		return (1);
	}
	return (0);
}

static inline void	reh1(t_map *self, uint32_t sz, uint8_t *bucks, uint32_t j)
{
	void			*key;
	void			*val;
	uint32_t		k;
	uint32_t		i;
	uint32_t		step;

	step = 0;
	key = *(void **)((char *)self->keys + (j * self->ksz));
	val = *(void **)((char *)self->vals + (j * self->vsz));
	BUCKET_SET_ISDEL_TRUE(self->bucks, j);
	while (1)
	{
		k = self->hasher.hash(key);
		i = k & (sz - 1);
		while (!BUCKET_ISEMPTY(bucks, i))
			i = (i + (++step)) & (sz - 1);
		BUCKET_SET_ISEMPTY_FALSE(bucks, i);
		if (hswap(self, &key, &val, i))
			break ;
	}
}

static inline void	reh(t_map *self, uint32_t sz, uint8_t *bucks)
{
	uint32_t		j;

	j = 0;
	while (j != self->cap)
	{
		if (BUCKET_ISEITHER(self->bucks, j) == 0)
			reh1(self, sz, bucks, j);
		++j;
	}
	if (self->cap > sz)
	{
		self->keys = ft_realloc(self->keys, self->len * self->ksz,
			sz * self->ksz);
		self->vals = ft_realloc(self->vals, self->len * self->vsz,
			sz * self->vsz);
	}
	free(self->bucks);
	self->bucks = bucks;
	self->cap = sz;
	self->occupieds = self->len;
	self->upper_bound = (uint32_t)(self->cap * MAP_HASH_UPPER + 0.5);
}

size_t				ft_maprsz(t_map *self, uint32_t sz)
{
	uint8_t			*bucks;
	uint32_t		j;

	j = 1;
	bucks = NULL;
	if ((sz = pow2_next32(sz)) < 32)
		sz = 32;
	if (self->len >= (uint32_t)(sz * MAP_HASH_UPPER + 0.5))
		j = 0;
	else
	{
		bucks = (uint8_t *)ft_malloc(sz);
		ft_memset(bucks, BUCKET_EMPTY, sz);
		if (self->cap < sz)
		{
			self->keys = ft_realloc(self->keys, self->len * self->ksz,
				sz * self->ksz);
			self->vals = ft_realloc(self->vals, self->len * self->vsz,
				sz * self->vsz);
		}
	}
	if (j)
		reh(self, sz, bucks);
	return (self->cap);
}
