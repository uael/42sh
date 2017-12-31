/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 08:28:36 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_di8_clean(t_di8 *self, t_dtor idtor)
{
	size_t	n;
	int8_t	*item;
	int8_t	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_di8_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int8_t));
	self->cur = 0;
	return (n);
}

inline size_t	ft_di16_clean(t_di16 *self, t_dtor idtor)
{
	size_t	n;
	int16_t	*item;
	int16_t	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_di16_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int16_t));
	self->cur = 0;
	return (n);
}

inline size_t	ft_di32_clean(t_di32 *self, t_dtor idtor)
{
	size_t	n;
	int32_t	*item;
	int32_t	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_di32_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int32_t));
	self->cur = 0;
	return (n);
}

inline size_t	ft_di64_clean(t_di64 *self, t_dtor idtor)
{
	size_t	n;
	int64_t	*item;
	int64_t	*it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_di64_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int64_t));
	self->cur = 0;
	return (n);
}

inline size_t	ft_dqstr_clean(t_dqstr *self, t_dtor idtor)
{
	size_t	n;
	char	**item;
	char	**it;

	if (!(n = self->cur) || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = self->buf;
	if (idtor)
	{
		item = it - 1;
		while (++item != ft_dqstr_begin(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(char *));
	self->cur = 0;
	return (n);
}
