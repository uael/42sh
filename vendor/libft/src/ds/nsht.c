/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sht.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline size_t	ft_deqnsht(t_deq *self, size_t n, void *out)
{
	size_t		len;
	uint64_t	*it;

	if (!n || (len = ft_deqlen(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_deqbeg(self);
	if (out)
		ft_memcpy(out, it, n * self->isz);
	self->cur += n;
	return (n);
}

inline size_t	ft_sdsnsht(t_sds *self, size_t n, char *out)
{
	size_t	len;
	char	*it;

	if (!n || (len = ft_sdslen(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_sdsbeg(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(char));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(char));
	self->buf[self->len] = '\0';
	return (n);
}

inline size_t	ft_vecnsht(t_vec *self, size_t n, void *out)
{
	size_t	len;
	char	*it;

	if (!n || (len = ft_veclen(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vecbeg(self);
	if (out)
		ft_memcpy(out, it, n * self->isz);
	if (self->len -= n)
		ft_memmove(it, it + (n * self->isz), (self->len + 1) * self->isz);
	return (n);
}
