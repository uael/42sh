/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 14:18:33 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline size_t	ft_deqclean(t_deq *self, t_dtor idtor)
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
		while ((item += self->isz) != ft_deqbeg(self))
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + (n * self->isz), (self->len + 1) * self->isz);
	self->cur = 0;
	return (n);
}

inline size_t	ft_vecclean(t_vec *self, size_t n, t_dtor idtor)
{
	char	*item;
	char	*it;
	char	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vecbeg(self);
	end = ft_vecat(self, n);
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
