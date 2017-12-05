/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_removen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline size_t	ft_vu8_removen(t_vu8 *self, size_t idx, size_t n, uint8_t *out)
{
	size_t	len;
	uint8_t	*it;

	if (idx >= (len = ft_vu8_size(self)))
		return (0);
	else if (idx == len - 1)
		return (ft_vu8_popn(self, n, out));
	else if (idx == 0)
		return (ft_vu8_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vu8_at(self, idx);
		if (out)
			ft_memcpy(out, it, n * sizeof(uint8_t));
		ft_memmove(it, it + n, (len - idx - n + 1) * sizeof(uint8_t));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_vu16_removen(t_vu16 *self, size_t i, size_t n, uint16_t *out)
{
	size_t		len;
	uint16_t	*it;

	if (i >= (len = ft_vu16_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_vu16_popn(self, n, out));
	else if (i == 0)
		return (ft_vu16_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vu16_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(uint16_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(uint16_t));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_vu32_removen(t_vu32 *self, size_t i, size_t n, uint32_t *out)
{
	size_t		len;
	uint32_t	*it;

	if (i >= (len = ft_vu32_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_vu32_popn(self, n, out));
	else if (i == 0)
		return (ft_vu32_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vu32_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(uint32_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(uint32_t));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_vu64_removen(t_vu64 *self, size_t i, size_t n, uint64_t *out)
{
	size_t		len;
	uint64_t	*it;

	if (i >= (len = ft_vu64_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_vu64_popn(self, n, out));
	else if (i == 0)
		return (ft_vu64_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vu64_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(uint64_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(uint64_t));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_vec_removen(t_vec *s, size_t i, size_t n, void *out)
{
	size_t	len;
	char	*it;

	if (i >= (len = ft_vec_size(s)))
		return (0);
	else if (i == len - 1)
		return (ft_vec_popn(s, n, out));
	else if (i == 0)
		return (ft_vec_shiftn(s, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vec_at(s, i);
		if (out)
			ft_memcpy(out, it, n * s->isz);
		len = len - i - n + 1;
		ft_memmove(it, it + (n * s->isz), len * s->isz);
		s->len -= n;
		return (n);
	}
}
