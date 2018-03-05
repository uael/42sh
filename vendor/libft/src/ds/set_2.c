/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

t_bool					ft_setget(t_set *self, void *k, uint32_t *out)
{
	uint32_t	i;
	uint32_t	last;
	uint32_t	mask;
	uint32_t	step;

	if (!self->cap)
		return (0);
	step = 0;
	mask = self->cap - 1;
	i = self->hasher.hash(k) & mask;
	last = i;
	while ((self->bucks[i] & BUCKET_EMPTY) != BUCKET_EMPTY &&
		((self->bucks[i] & BUCKET_DELETED) == BUCKET_DELETED ||
		!self->hasher.eq(*(void **)((char *)self->keys + (i * self->ksz)), k)))
	{
		i = (i + (++step)) & mask;
		if (i == last)
			return (0);
	}
	if (self->bucks[i] & BUCKET_BOTH)
		return (0);
	if (out)
		*out = i;
	return (1);
}

static inline uint32_t	setput(t_set *s, void *key)
{
	uint32_t i;
	uint32_t last;
	uint32_t mask;
	uint32_t step;

	step = 0;
	if (s->occupieds >= s->upper_bound)
		ft_setrsz(s, s->cap > (s->len << 1)
			? s->cap - 1 : s->cap + 1);
	mask = s->cap - 1;
	i = s->hasher.hash(key) & mask;
	last = i;
	while (1)
		if (s->bucks[i] & BUCKET_EMPTY ||
			(!(s->bucks[i] & BUCKET_DELETED) &&
			s->hasher.eq(*(void **)((char *)s->keys + (i * s->ksz)), key)))
			break ;
		else if ((i = (i + (++step)) & mask) == last)
			break ;
	return (i);
}

t_bool					ft_setput(t_set *self, void *key, uint32_t *out)
{
	uint32_t x;

	x = setput(self, key);
	if (out)
		*out = x;
	if ((self->bucks[x] & BUCKET_EMPTY) == BUCKET_EMPTY)
	{
		*(void **)((char *)self->keys + (x * self->ksz)) = key;
		self->bucks[x] = 0;
		++self->len;
		++self->occupieds;
		return (1);
	}
	else if ((self->bucks[x] & BUCKET_DELETED) == BUCKET_DELETED)
	{
		*(void **)((char *)self->keys + (x * self->ksz)) = key;
		self->bucks[x] = 0;
		++self->len;
		return (1);
	}
	return (0);
}
