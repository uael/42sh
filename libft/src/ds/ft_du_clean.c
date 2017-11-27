/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 14:18:33 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

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
