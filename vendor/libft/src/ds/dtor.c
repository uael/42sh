/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 14:18:33 by null             ###   ########.fr       */
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
	FT_INIT(self, t_deq);
}

void		ft_mapdtor(t_map *self, t_dtor kdtor, t_dtor vdtor)
{
	uint32_t	it;

	if (self->bucks)
	{
		if (kdtor || vdtor)
		{
			it = 0;
			while (it < self->len)
			{
				if (BUCKET_ISPOPULATED(self->bucks, it))
				{
					if (kdtor)
						kdtor(self->keys + (it * self->ksz));
					if (vdtor)
						vdtor(self->vals + (it * self->vsz));
				}
				++it;
			}
		}
		free(self->bucks);
		free(self->keys);
		free(self->vals);
    }
}

inline void	ft_sdsdtor(t_sds *self)
{
	if (self->buf)
		free(self->buf);
	FT_INIT(self, t_sds);
}

inline void	ft_vecdtor(t_vec *self, t_dtor idtor)
{
	char	*item;

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
	FT_INIT(self, t_vec);
}
