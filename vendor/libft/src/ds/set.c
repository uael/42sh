/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

static inline char	hswap(t_set *self, void **key, uint32_t i)
{
	void			*tmp;

	if (i < self->cap && !(self->bucks[i] & BUCKET_BOTH))
	{
		tmp = *(void **)((char *)self->keys + (i * self->ksz));
		*(void **)((char *)self->keys + (i * self->ksz)) = *key;
		*key = tmp;
		self->bucks[i] |= BUCKET_DELETED;
	}
	else
	{
		*(void **)((char *)self->keys + (i * self->ksz)) = *key;
		return (1);
	}
	return (0);
}

static inline void	reh1(t_set *self, uint32_t sz, uint8_t *bucks, uint32_t j)
{
	void			*key;
	uint32_t		k;
	uint32_t		i;
	uint32_t		step;

	step = 0;
	key = *(void **)((char *)self->keys + (j * self->ksz));
	self->bucks[j] |= BUCKET_DELETED;
	while (1)
	{
		k = self->hasher.hash(key);
		i = k & (sz - 1);
		while ((bucks[i] & BUCKET_EMPTY) != BUCKET_EMPTY)
			i = (i + (++step)) & (sz - 1);
		bucks[i] &= ~BUCKET_EMPTY;
		if (hswap(self, &key, i))
			break ;
	}
}

static inline void	reh(t_set *self, uint32_t sz, uint8_t *bucks)
{
	uint32_t		j;

	j = 0;
	while (j != self->cap)
	{
		if (!(self->bucks[j] & BUCKET_BOTH))
			reh1(self, sz, bucks, j);
		++j;
	}
	if (self->cap > sz)
		self->keys = ft_realloc(self->keys, self->len * self->ksz,
			sz * self->ksz);
	free(self->bucks);
	self->bucks = bucks;
	self->cap = sz;
	self->occupieds = self->len;
	self->upper_bound = (uint32_t)(self->cap * MAP_HASH_UPPER + 0.5);
}

size_t				ft_setrsz(t_set *self, uint32_t sz)
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
			self->keys = ft_realloc(self->keys, self->len * self->ksz,
				sz * self->ksz);
	}
	if (j)
		reh(self, sz, bucks);
	return (self->cap);
}
