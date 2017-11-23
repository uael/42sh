/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_pushn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_pushn(t_di8 *self, size_t n)
{
	int8_t *it;

	if (!n || !ft_di8_grow(self, n))
		return (NULL);
	it = ft_di8_end(self);
	self->len += n;
	return (it);
}

inline int16_t	*ft_di16_pushn(t_di16 *self, size_t n)
{
	int16_t *it;

	if (!n || !ft_di16_grow(self, n))
		return (NULL);
	it = ft_di16_end(self);
	self->len += n;
	return (it);
}

inline int32_t	*ft_di32_pushn(t_di32 *self, size_t n)
{
	int32_t *it;

	if (!n || !ft_di32_grow(self, n))
		return (NULL);
	it = ft_di32_end(self);
	self->len += n;
	return (it);
}

inline int64_t	*ft_di64_pushn(t_di64 *self, size_t n)
{
	int64_t *it;

	if (!n || !ft_di64_grow(self, n))
		return (NULL);
	it = ft_di64_end(self);
	self->len += n;
	return (it);
}

inline char		**ft_dqstr_pushn(t_dqstr *self, size_t n)
{
	char **it;

	if (!n || !ft_dqstr_grow(self, n))
		return (NULL);
	it = ft_dqstr_end(self);
	self->len += n;
	return (it);
}
