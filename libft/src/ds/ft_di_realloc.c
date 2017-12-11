/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 12:21:07 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_di8_realloc(t_di8 *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(int8_t),
		n * sizeof(int8_t))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}

inline t_bool	ft_di16_realloc(t_di16 *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(int16_t),
		n * sizeof(int16_t))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}

inline t_bool	ft_di32_realloc(t_di32 *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(int32_t),
		n * sizeof(int32_t))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}

inline t_bool	ft_di64_realloc(t_di64 *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(int64_t),
		n * sizeof(int64_t))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}

inline t_bool	ft_dqstr_realloc(t_dqstr *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len * sizeof(char *),
		n * sizeof(char *))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}
