/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:05:48 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_putn(t_vu8 *self, size_t idx, size_t n)
{
	size_t	len;
	uint8_t	*it;

	if (idx == 0)
		return (ft_vu8_unshiftn(self, n));
	else if (idx == (len = ft_vu8_size(self)))
		return (ft_vu8_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vu8_grow(self, n);
		it = ft_vu8_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int8_t));
		self->len += n;
		return (it);
	}
}

inline uint16_t	*ft_vu16_putn(t_vu16 *self, size_t idx, size_t n)
{
	size_t		len;
	uint16_t	*it;

	if (idx == 0)
		return (ft_vu16_unshiftn(self, n));
	else if (idx == (len = ft_vu16_size(self)))
		return (ft_vu16_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vu16_grow(self, n);
		it = ft_vu16_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int16_t));
		self->len += n;
		return (it);
	}
}

inline uint32_t	*ft_vu32_putn(t_vu32 *self, size_t idx, size_t n)
{
	size_t		len;
	uint32_t	*it;

	if (idx == 0)
		return (ft_vu32_unshiftn(self, n));
	else if (idx == (len = ft_vu32_size(self)))
		return (ft_vu32_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vu32_grow(self, n);
		it = ft_vu32_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int32_t));
		self->len += n;
		return (it);
	}
}

inline uint64_t	*ft_vu64_putn(t_vu64 *self, size_t idx, size_t n)
{
	size_t		len;
	uint64_t	*it;

	if (idx == 0)
		return (ft_vu64_unshiftn(self, n));
	else if (idx == (len = ft_vu64_size(self)))
		return (ft_vu64_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vu64_grow(self, n);
		it = ft_vu64_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int64_t));
		self->len += n;
		return (it);
	}
}

inline void		*ft_vec_putn(t_vec *self, size_t idx, size_t n)
{
	size_t	len;
	void	*it;

	if (idx == 0)
		return (ft_vec_unshiftn(self, n));
	else if (idx == (len = ft_vec_size(self)))
		return (ft_vec_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vec_grow(self, n);
		it = ft_vec_at(self, idx);
		ft_memmove((char *)it + (n * self->isz), it,
			(len - idx + 1) * self->isz);
		self->len += n;
		return (it);
	}
}
