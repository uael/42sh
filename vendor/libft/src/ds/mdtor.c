/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdtor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 14:18:33 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	ft_deqmdtor(t_deq *self, t_dtor idtor)
{
	char	*item;

	if (self->cap)
	{
		if (idtor)
		{
			item = self->buf - self->isz;
			while ((item += self->isz) <= (char *)self->buf +
				(self->len * self->isz))
				idtor(item);
		}
		free(self->buf);
	}
	ft_bzero(self, sizeof(t_deq));
}

inline void	ft_vecmdtor(t_vec *self, t_dtor idtor)
{
	char	*item;

	if (self->cap)
	{
		if (idtor)
		{
			item = self->buf - self->isz;
			while ((item += self->isz) <= (char *)self->buf +
				(self->len * self->isz))
				idtor(item);
		}
		free(self->buf);
	}
	ft_bzero(self, sizeof(t_vec));
}
