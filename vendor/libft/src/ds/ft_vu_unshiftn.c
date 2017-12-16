/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_unshiftn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_unshiftn(t_vu8 *self, size_t n)
{
	size_t	len;
	uint8_t	*it;

	if (!n || !ft_vu8_grow(self, n))
		return (NULL);
	it = ft_vu8_begin(self);
	if ((len = ft_vu8_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int8_t));
	self->len += n;
	return (it);
}

inline uint16_t	*ft_vu16_unshiftn(t_vu16 *self, size_t n)
{
	size_t		len;
	uint16_t	*it;

	if (!n || !ft_vu16_grow(self, n))
		return (NULL);
	it = ft_vu16_begin(self);
	if ((len = ft_vu16_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int16_t));
	self->len += n;
	return (it);
}

inline uint32_t	*ft_vu32_unshiftn(t_vu32 *self, size_t n)
{
	size_t		len;
	uint32_t	*it;

	if (!n || !ft_vu32_grow(self, n))
		return (NULL);
	it = ft_vu32_begin(self);
	if ((len = ft_vu32_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int32_t));
	self->len += n;
	return (it);
}

inline uint64_t	*ft_vu64_unshiftn(t_vu64 *self, size_t n)
{
	size_t		len;
	uint64_t	*it;

	if (!n || !ft_vu64_grow(self, n))
		return (NULL);
	it = ft_vu64_begin(self);
	if ((len = ft_vu64_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int64_t));
	self->len += n;
	return (it);
}

inline void		*ft_vec_unshiftn(t_vec *self, size_t n)
{
	size_t	len;
	void	*it;

	if (!n || !ft_vec_grow(self, n))
		return (NULL);
	it = ft_vec_begin(self);
	if ((len = ft_vec_size(self)))
		ft_memmove((char *)it + (n * self->isz), it,
			(len + 1) * self->isz);
	self->len += n;
	return (it);
}
