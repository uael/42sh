/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_removen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_du8_removen(t_du8 *self, size_t idx, size_t n, uint8_t *out)
{
	size_t	len;
	uint8_t	*it;

	if (idx >= (len = ft_du8_size(self)))
		return (0);
	else if (idx == len - 1)
		return (ft_du8_popn(self, n, out));
	else if (idx == 0)
		return (ft_du8_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_du8_at(self, idx);
		if (out)
			ft_memcpy(out, it, n * sizeof(uint8_t));
		ft_memmove(it, it + n, (len - idx - n + 1) * sizeof(uint8_t));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_du16_removen(t_du16 *self, size_t i, size_t n, uint16_t *out)
{
	size_t		len;
	uint16_t	*it;

	if (i >= (len = ft_du16_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_du16_popn(self, n, out));
	else if (i == 0)
		return (ft_du16_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_du16_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(uint16_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(uint16_t));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_du32_removen(t_du32 *self, size_t i, size_t n, uint32_t *out)
{
	size_t		len;
	uint32_t	*it;

	if (i >= (len = ft_du32_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_du32_popn(self, n, out));
	else if (i == 0)
		return (ft_du32_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_du32_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(uint32_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(uint32_t));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_du64_removen(t_du64 *self, size_t i, size_t n, uint64_t *out)
{
	size_t		len;
	uint64_t	*it;

	if (i >= (len = ft_du64_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_du64_popn(self, n, out));
	else if (i == 0)
		return (ft_du64_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_du64_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(uint64_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(uint64_t));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_deq_removen(t_deq *s, size_t i, size_t n, void *out)
{
	size_t	len;
	char	*it;

	if (i >= (len = ft_deq_size(s)))
		return (0);
	else if (i == len - 1)
		return (ft_deq_popn(s, n, out));
	else if (i == 0)
		return (ft_deq_shiftn(s, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_deq_at(s, i);
		if (out)
			ft_memcpy(out, it, n * s->isz);
		len = len - i - n + 1;
		ft_memmove(it, it + (n * s->isz), len * s->isz);
		s->len -= n;
		return (n);
	}
}
