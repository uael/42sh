/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 08:18:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline void	ft_du8_clear(t_du8 *self, t_dtor idtor)
{
	uint8_t	*item;

	if (self->buf && idtor)
	{
		item = ft_du8_begin(self);
		while (item != ft_du8_end(self))
			idtor(item++);
		self->len = self->cur;
	}
}

inline void	ft_du16_clear(t_du16 *self, t_dtor idtor)
{
	uint16_t	*item;

	if (self->buf && idtor)
	{
		item = ft_du16_begin(self);
		while (item != ft_du16_end(self))
			idtor(item++);
		self->len = self->cur;
	}
}

inline void	ft_du32_clear(t_du32 *self, t_dtor idtor)
{
	uint32_t	*item;

	if (self->buf && idtor)
	{
		item = ft_du32_begin(self);
		while (item != ft_du32_end(self))
			idtor(item++);
		self->len = self->cur;
	}
}

inline void	ft_du64_clear(t_du64 *self, t_dtor idtor)
{
	uint64_t	*item;

	if (self->buf && idtor)
	{
		item = ft_du64_begin(self);
		while (item != ft_du64_end(self))
			idtor(item++);
		self->len = self->cur;
	}
}

inline void	ft_deq_clear(t_deq *self, t_dtor idtor)
{
	char	*item;

	if (self->buf && idtor)
	{
		item = ft_deq_begin(self) - self->isz;
		while ((item += self->isz) != ft_deq_end(self))
			idtor(item);
		self->len = self->cur;
	}
}
