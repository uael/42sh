/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 08:28:36 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_du8_clean(t_du8 *self, t_dtor idtor)
{
	size_t	n;
	uint8_t	*item;
	uint8_t	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_du8_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint8_t));
	self->cur = 0;
	return (n);
}

inline size_t	ft_du16_clean(t_du16 *self, t_dtor idtor)
{
	size_t		n;
	uint16_t	*item;
	uint16_t	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_du16_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint16_t));
	self->cur = 0;
	return (n);
}

inline size_t	ft_du32_clean(t_du32 *self, t_dtor idtor)
{
	size_t		n;
	uint32_t	*item;
	uint32_t	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_du32_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint32_t));
	self->cur = 0;
	return (n);
}

inline size_t	ft_du64_clean(t_du64 *self, t_dtor idtor)
{
	size_t		n;
	uint64_t	*item;
	uint64_t	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_du64_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint64_t));
	self->cur = 0;
	return (n);
}

inline size_t	ft_deq_clean(t_deq *self, t_dtor idtor)
{
	size_t	n;
	char	*item;
	char	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - self->isz;
		while ((item += self->isz) != ft_deq_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + (n * self->isz), (self->len + 1) * self->isz);
	self->cur = 0;
	return (n);
}
