/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

t_bool	ft_mapget(t_map *self, void *key, uint32_t *out)
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
	while (!BUCKET_ISEMPTY(self->bucks, i) &&
		(BUCKET_ISDEL(self->bucks, i) ||
		!self->hasher.eq(*(void **)((char *)self->keys + (i * self->ksz)), key)))
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
