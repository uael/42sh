/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline t_bool	ft_vi8_realloc(t_vi8 *self, size_t n)
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

inline t_bool	ft_vi16_realloc(t_vi16 *self, size_t n)
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

inline t_bool	ft_vi32_realloc(t_vi32 *self, size_t n)
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

inline t_bool	ft_vi64_realloc(t_vi64 *self, size_t n)
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

inline t_bool	ft_vstr_realloc(t_vstr *self, size_t n)
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
