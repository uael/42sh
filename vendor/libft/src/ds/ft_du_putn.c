/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:05:48 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_putn(t_du8 *self, size_t idx, size_t n)
{
	size_t	len;
	uint8_t	*it;

	if (idx == 0)
		return (ft_du8_unshiftn(self, n));
	else if (idx == (len = ft_du8_size(self)))
		return (ft_du8_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_du8_grow(self, n);
		it = ft_du8_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int8_t));
		self->len += n;
		return (it);
	}
}

inline uint16_t	*ft_du16_putn(t_du16 *self, size_t idx, size_t n)
{
	size_t		len;
	uint16_t	*it;

	if (idx == 0)
		return (ft_du16_unshiftn(self, n));
	else if (idx == (len = ft_du16_size(self)))
		return (ft_du16_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_du16_grow(self, n);
		it = ft_du16_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int16_t));
		self->len += n;
		return (it);
	}
}

inline uint32_t	*ft_du32_putn(t_du32 *self, size_t idx, size_t n)
{
	size_t		len;
	uint32_t	*it;

	if (idx == 0)
		return (ft_du32_unshiftn(self, n));
	else if (idx == (len = ft_du32_size(self)))
		return (ft_du32_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_du32_grow(self, n);
		it = ft_du32_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int32_t));
		self->len += n;
		return (it);
	}
}

inline uint64_t	*ft_du64_putn(t_du64 *self, size_t idx, size_t n)
{
	size_t		len;
	uint64_t	*it;

	if (idx == 0)
		return (ft_du64_unshiftn(self, n));
	else if (idx == (len = ft_du64_size(self)))
		return (ft_du64_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_du64_grow(self, n);
		it = ft_du64_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int64_t));
		self->len += n;
		return (it);
	}
}

inline void		*ft_deq_putn(t_deq *self, size_t idx, size_t n)
{
	size_t	len;
	void	*it;

	if (idx == 0)
		return (ft_deq_unshiftn(self, n));
	else if (idx == (len = ft_deq_size(self)))
		return (ft_deq_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_deq_grow(self, n);
		it = ft_deq_at(self, idx);
		ft_memmove((char *)it + (n * self->isz), it,
			(len - idx + 1) * self->isz);
		self->len += n;
		return (it);
	}
}
