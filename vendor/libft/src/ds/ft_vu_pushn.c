/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_pushn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:04:53 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_pushn(t_vu8 *self, size_t n)
{
	uint8_t *it;

	if (!n || !ft_vu8_grow(self, n))
		return (NULL);
	it = ft_vu8_end(self);
	self->len += n;
	return (it);
}

inline uint16_t	*ft_vu16_pushn(t_vu16 *self, size_t n)
{
	uint16_t *it;

	if (!n || !ft_vu16_grow(self, n))
		return (NULL);
	it = ft_vu16_end(self);
	self->len += n;
	return (it);
}

inline uint32_t	*ft_vu32_pushn(t_vu32 *self, size_t n)
{
	uint32_t *it;

	if (!n || !ft_vu32_grow(self, n))
		return (NULL);
	it = ft_vu32_end(self);
	self->len += n;
	return (it);
}

inline uint64_t	*ft_vu64_pushn(t_vu64 *self, size_t n)
{
	uint64_t *it;

	if (!n || !ft_vu64_grow(self, n))
		return (NULL);
	it = ft_vu64_end(self);
	self->len += n;
	return (it);
}

inline void		*ft_vec_pushn(t_vec *self, size_t n)
{
	void *it;

	if (!n || !ft_vec_grow(self, n))
		return (NULL);
	it = ft_vec_end(self);
	self->len += n;
	return (it);
}
