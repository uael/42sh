/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline size_t	ft_deqalloc(t_deq *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (self->cap);
	buf = ft_realloc(self->buf, self->len * self->isz, n * self->isz);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (self->cap);
}

inline size_t	ft_sdsalloc(t_sds *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (self->cap);
	buf = ft_realloc(self->buf, self->len, n * sizeof(char));
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (self->cap);
}

inline size_t	ft_vecalloc(t_vec *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (self->cap);
	buf = ft_realloc(self->buf, self->len * self->isz, n * self->isz);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (self->cap);
}
