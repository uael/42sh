/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	ft_deqclear(t_deq *self, t_dtor idtor)
{
	char	*item;

	if (self->buf && idtor)
	{
		item = ft_deqbeg(self) - self->isz;
		while ((item += self->isz) != ft_deqend(self))
			idtor(item);
		self->len = self->cur;
	}
}

inline void	ft_mapclr(t_map *self)
{
	if (self->bucks)
	{
		ft_memset(self->bucks, BUCKET_EMPTY, self->cap);
		self->len = 0;
		self->occupieds = 0;
	}
}

inline void	ft_vecclear(t_vec *self, t_dtor idtor)
{
	char	*item;

	if (self->buf && idtor)
	{
		item = (char *) ft_vecbeg(self) - self->isz;
		while ((item += self->isz) != (char *)ft_vecend(self))
			idtor(item);
		self->len = 0;
	}
}
