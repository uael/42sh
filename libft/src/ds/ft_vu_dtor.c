/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_dtor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 14:18:33 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline void	ft_vu8_dtor(t_vu8 *self, void (*idtor)(uint8_t *i))
{
	uint8_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vu8_begin(self);
			while (item != ft_vu8_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vu8);
}

inline void	ft_vu16_dtor(t_vu16 *self, void (*idtor)(uint16_t *i))
{
	uint16_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vu16_begin(self);
			while (item != ft_vu16_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vu16);
}

inline void	ft_vu32_dtor(t_vu32 *self, void (*idtor)(uint32_t *i))
{
	uint32_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vu32_begin(self);
			while (item != ft_vu32_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vu16);
}

inline void	ft_vu64_dtor(t_vu64 *self, void (*idtor)(uint64_t *i))
{
	uint64_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vu64_begin(self);
			while (item != ft_vu64_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vu64);
}

inline void	ft_vec_dtor(t_vec *self, t_dtor idtor)
{
	char	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vec_begin(self) - self->isz;
			while ((item += self->isz) != ft_vec_end(self))
				idtor(item);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vu64);
}
