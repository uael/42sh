/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_du8_realloc(t_du8 *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(uint8_t),
		n * sizeof(uint8_t))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}

inline t_bool	ft_du16_realloc(t_du16 *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(uint16_t),
		n * sizeof(uint16_t))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}

inline t_bool	ft_du32_realloc(t_du32 *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(uint32_t),
		n * sizeof(uint32_t))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}

inline t_bool	ft_du64_realloc(t_du64 *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(uint64_t),
		n * sizeof(uint64_t))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}

inline t_bool	ft_deq_realloc(t_deq *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * self->isz, n * self->isz)))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}
