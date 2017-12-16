/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_shiftn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:31:13 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_du8_shiftn(t_du8 *self, size_t n, uint8_t *out)
{
	size_t	len;
	uint8_t	*it;

	if (!n || (len = ft_du8_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_du8_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(uint8_t));
	self->cur += n;
	return (n);
}

inline size_t	ft_du16_shiftn(t_du16 *self, size_t n, uint16_t *out)
{
	size_t		len;
	uint16_t	*it;

	if (!n || (len = ft_du16_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_du16_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(uint16_t));
	self->cur += n;
	return (n);
}

inline size_t	ft_du32_shiftn(t_du32 *self, size_t n, uint32_t *out)
{
	size_t		len;
	uint32_t	*it;

	if (!n || (len = ft_du32_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_du32_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(uint32_t));
	self->cur += n;
	return (n);
}

inline size_t	ft_du64_shiftn(t_du64 *self, size_t n, uint64_t *out)
{
	size_t		len;
	uint64_t	*it;

	if (!n || (len = ft_du64_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_du64_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(uint64_t));
	self->cur += n;
	return (n);
}

inline size_t	ft_deq_shiftn(t_deq *self, size_t n, void *out)
{
	size_t		len;
	uint64_t	*it;

	if (!n || (len = ft_deq_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_deq_begin(self);
	if (out)
		ft_memcpy(out, it, n * self->isz);
	self->cur += n;
	return (n);
}
