/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_pushn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:04:53 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_pushn(t_du8 *self, size_t n)
{
	uint8_t *it;

	if (!n || !ft_du8_grow(self, n))
		return (NULL);
	it = ft_du8_end(self);
	self->len += n;
	return (it);
}

inline uint16_t	*ft_du16_pushn(t_du16 *self, size_t n)
{
	uint16_t *it;

	if (!n || !ft_du16_grow(self, n))
		return (NULL);
	it = ft_du16_end(self);
	self->len += n;
	return (it);
}

inline uint32_t	*ft_du32_pushn(t_du32 *self, size_t n)
{
	uint32_t *it;

	if (!n || !ft_du32_grow(self, n))
		return (NULL);
	it = ft_du32_end(self);
	self->len += n;
	return (it);
}

inline uint64_t	*ft_du64_pushn(t_du64 *self, size_t n)
{
	uint64_t *it;

	if (!n || !ft_du64_grow(self, n))
		return (NULL);
	it = ft_du64_end(self);
	self->len += n;
	return (it);
}

inline void		*ft_deq_pushn(t_deq *self, size_t n)
{
	uint64_t *it;

	if (!n || !ft_deq_grow(self, n))
		return (NULL);
	it = ft_deq_end(self);
	self->len += n;
	return (it);
}
