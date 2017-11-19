/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_pushn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_pushn(t_vi8 *self, size_t n)
{
	int8_t *it;

	if (!n || !ft_vi8_grow(self, n))
		return (NULL);
	it = ft_vi8_end(self);
	self->len += n;
	return (it);
}

inline int16_t	*ft_vi16_pushn(t_vi16 *self, size_t n)
{
	int16_t *it;

	if (!n || !ft_vi16_grow(self, n))
		return (NULL);
	it = ft_vi16_end(self);
	self->len += n;
	return (it);
}

inline int32_t	*ft_vi32_pushn(t_vi32 *self, size_t n)
{
	int32_t *it;

	if (!n || !ft_vi32_grow(self, n))
		return (NULL);
	it = ft_vi32_end(self);
	self->len += n;
	return (it);
}

inline int64_t	*ft_vi64_pushn(t_vi64 *self, size_t n)
{
	int64_t *it;

	if (!n || !ft_vi64_grow(self, n))
		return (NULL);
	it = ft_vi64_end(self);
	self->len += n;
	return (it);
}

inline char		**ft_vstr_pushn(t_vstr *self, size_t n)
{
	char **it;

	if (!n || !ft_vstr_grow(self, n))
		return (NULL);
	it = ft_vstr_end(self);
	self->len += n;
	return (it);
}
