/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline void	ft_vu8_clear(t_vu8 *self, t_dtor idtor)
{
	uint8_t	*item;

	if (self->buf && idtor)
	{
		item = ft_vu8_begin(self);
		while (item != ft_vu8_end(self))
			idtor(item++);
		self->len = 0;
	}
}

inline void	ft_vu16_clear(t_vu16 *self, t_dtor idtor)
{
	uint16_t	*item;

	if (self->buf && idtor)
	{
		item = ft_vu16_begin(self);
		while (item != ft_vu16_end(self))
			idtor(item++);
		self->len = 0;
	}
}

inline void	ft_vu32_clear(t_vu32 *self, t_dtor idtor)
{
	uint32_t	*item;

	if (self->buf && idtor)
	{
		item = ft_vu32_begin(self);
		while (item != ft_vu32_end(self))
			idtor(item++);
		self->len = 0;
	}
}

inline void	ft_vu64_clear(t_vu64 *self, t_dtor idtor)
{
	uint64_t	*item;

	if (self->buf && idtor)
	{
		item = ft_vu64_begin(self);
		while (item != ft_vu64_end(self))
			idtor(item++);
		self->len = 0;
	}
}

inline void	ft_vec_clear(t_vec *self, t_dtor idtor)
{
	char	*item;

	if (self->buf && idtor)
	{
		item = (char *)ft_vec_begin(self) - self->isz;
		while ((item += self->isz) != (char *)ft_vec_end(self))
			idtor(item);
		self->len = 0;
	}
}
