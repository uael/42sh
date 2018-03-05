/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example/cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	ft_deqdtor(t_deq *self, t_dtor idtor)
{
	char	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_deqbeg(self) - self->isz;
			while ((item += self->isz) != ft_deqend(self))
				idtor(item);
		}
		free(self->buf);
	}
	ft_bzero(self, sizeof(t_deq));
}

void		ft_mapdtor(t_map *self, t_dtor kdtor, t_dtor vdtor)
{
	uint32_t	it;

	if (self->bucks)
	{
		if (kdtor || vdtor)
		{
			it = 0;
			while (it < self->cap)
			{
				if (!(self->bucks[it] & BUCKET_BOTH) ||
					(self->bucks[it] & BUCKET_DELETED) == BUCKET_DELETED)
				{
					if (kdtor)
						kdtor(self->keys + (it * self->ksz));
					if (vdtor)
						vdtor(self->vals + (it * self->vsz));
				}
				++it;
			}
		}
		ft_pfree((void **)&self->bucks);
		ft_pfree(&self->keys);
		ft_pfree(&self->vals);
	}
}

void		ft_setdtor(t_set *self, t_dtor kdtor)
{
	uint32_t	it;

	if (self->bucks)
	{
		if (kdtor)
		{
			it = 0;
			while (it < self->cap)
			{
				if (!(self->bucks[it] & BUCKET_BOTH) ||
					(self->bucks[it] & BUCKET_DELETED) == BUCKET_DELETED)
					kdtor(self->keys + (it * self->ksz));
				++it;
			}
		}
		ft_pfree((void **)&self->bucks);
		ft_pfree(&self->keys);
	}
}

inline void	ft_sdsdtor(t_sds *self)
{
	if (self->buf)
		free(self->buf);
	self->buf = NULL;
	self->cap = 0;
	self->len = 0;
}

inline void	ft_vecdtor(t_vec *self, t_dtor idtor)
{
	char *item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vecbeg(self) - self->isz;
			while ((item += self->isz) != ft_vecend(self))
				idtor(item);
		}
		free(self->buf);
	}
	ft_bzero(self, sizeof(t_vec));
}
