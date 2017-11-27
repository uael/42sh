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
