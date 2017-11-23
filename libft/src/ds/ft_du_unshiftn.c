/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_unshiftn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:31:13 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_unshiftn(t_du8 *self, size_t n)
{
	size_t	len;
	uint8_t	*it;

	if (!n || !ft_du8_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_du8_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_du8_begin(self);
	if ((len = ft_du8_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int8_t));
	self->len += n;
	return (it);
}

inline uint16_t	*ft_du16_unshiftn(t_du16 *self, size_t n)
{
	size_t		len;
	uint16_t	*it;

	if (!n || !ft_du16_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_du16_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_du16_begin(self);
	if ((len = ft_du16_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int16_t));
	self->len += n;
	return (it);
}

inline uint32_t	*ft_du32_unshiftn(t_du32 *self, size_t n)
{
	size_t		len;
	uint32_t	*it;

	if (!n || !ft_du32_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_du32_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_du32_begin(self);
	if ((len = ft_du32_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int32_t));
	self->len += n;
	return (it);
}

inline uint64_t	*ft_du64_unshiftn(t_du64 *self, size_t n)
{
	size_t		len;
	uint64_t	*it;

	if (!n || !ft_du64_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_du64_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_du64_begin(self);
	if ((len = ft_du64_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int64_t));
	self->len += n;
	return (it);
}

inline void		*ft_deq_unshiftn(t_deq *self, size_t n)
{
	size_t	len;
	void	*it;

	if (!n || !ft_deq_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_deq_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_deq_begin(self);
	if ((len = ft_deq_size(self)))
		ft_memmove((char *)it + (n * self->isz), it,
			(len + 1) * self->isz);
	self->len += n;
	return (it);
}
