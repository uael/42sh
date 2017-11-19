/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_shiftn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline size_t	ft_vu8_shiftn(t_vu8 *self, size_t n, uint8_t *out)
{
	size_t	len;
	uint8_t	*it;

	if (!n || (len = ft_vu8_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vu8_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(uint8_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint8_t));
	return (n);
}

inline size_t	ft_vu16_shiftn(t_vu16 *self, size_t n, uint16_t *out)
{
	size_t		len;
	uint16_t	*it;

	if (!n || (len = ft_vu16_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vu16_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(uint16_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint16_t));
	return (n);
}

inline size_t	ft_vu32_shiftn(t_vu32 *self, size_t n, uint32_t *out)
{
	size_t		len;
	uint32_t	*it;

	if (!n || (len = ft_vu32_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vu32_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(uint32_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint32_t));
	return (n);
}

inline size_t	ft_vu64_shiftn(t_vu64 *self, size_t n, uint64_t *out)
{
	size_t		len;
	uint64_t	*it;

	if (!n || (len = ft_vu64_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vu64_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(uint64_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(uint64_t));
	return (n);
}

inline size_t	ft_vec_shiftn(t_vec *self, size_t n, void *out)
{
	size_t		len;
	uint64_t	*it;

	if (!n || (len = ft_vec_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vec_begin(self);
	if (out)
		ft_memcpy(out, it, n * self->isz);
	if (self->len -= n)
		ft_memmove(it, (char *)it + (n * self->isz),
			(self->len + 1) * self->isz);
	return (n);
}
