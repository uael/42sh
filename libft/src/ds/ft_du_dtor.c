/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_dtor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 14:18:33 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline void	ft_du8_dtor(t_du8 *self, void (*idtor)(uint8_t *i))
{
	uint8_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_du8_begin(self);
			while (item != ft_du8_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_du8);
}

inline void	ft_du16_dtor(t_du16 *self, void (*idtor)(uint16_t *i))
{
	uint16_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_du16_begin(self);
			while (item != ft_du16_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_du16);
}

inline void	ft_du32_dtor(t_du32 *self, void (*idtor)(uint32_t *i))
{
	uint32_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_du32_begin(self);
			while (item != ft_du32_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_du16);
}

inline void	ft_du64_dtor(t_du64 *self, void (*idtor)(uint64_t *i))
{
	uint64_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_du64_begin(self);
			while (item != ft_du64_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_du64);
}

inline void	ft_deq_dtor(t_deq *self, void (*idtor)(void *i))
{
	char	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_deq_begin(self) - self->isz;
			while ((item += self->isz) != ft_deq_end(self))
				idtor(item);
		}
		free(self->buf);
	}
	FT_INIT(self, t_deq);
}
