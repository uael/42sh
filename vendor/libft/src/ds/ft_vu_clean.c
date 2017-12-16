/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 14:18:33 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline size_t	ft_vu8_clean(t_vu8 *self, size_t n, t_dtor idtor)
{
	uint8_t	*item;
	uint8_t	*it;
	uint8_t	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vu8_begin(self);
	end = ft_vu8_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint8_t));
	return (n);
}

inline size_t	ft_vu16_clean(t_vu16 *self, size_t n, t_dtor idtor)
{
	uint16_t	*item;
	uint16_t	*it;
	uint16_t	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vu16_begin(self);
	end = ft_vu16_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint16_t));
	return (n);
}

inline size_t	ft_vu32_clean(t_vu32 *self, size_t n, t_dtor idtor)
{
	uint32_t	*item;
	uint32_t	*it;
	uint32_t	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vu32_begin(self);
	end = ft_vu32_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint32_t));
	return (n);
}

inline size_t	ft_vu64_clean(t_vu64 *self, size_t n, t_dtor idtor)
{
	uint64_t	*item;
	uint64_t	*it;
	uint64_t	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vu64_begin(self);
	end = ft_vu64_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint64_t));
	return (n);
}

inline size_t	ft_vec_clean(t_vec *self, size_t n, t_dtor idtor)
{
	char	*item;
	char	*it;
	char	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vec_begin(self);
	end = ft_vec_at(self, n);
	if (idtor)
	{
		item = it - self->isz;
		while ((item += self->isz) != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + (n * self->isz), (self->len + 1) * self->isz);
	return (n);
}
