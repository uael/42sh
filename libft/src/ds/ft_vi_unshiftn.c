/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_unshiftn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_unshiftn(t_vi8 *self, size_t n)
{
	size_t	len;
	int8_t	*it;

	if (!n || !ft_vi8_grow(self, n))
		return (NULL);
	it = ft_vi8_begin(self);
	if ((len = ft_vi8_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int8_t));
	self->len += n;
	return (it);
}

inline int16_t	*ft_vi16_unshiftn(t_vi16 *self, size_t n)
{
	size_t	len;
	int16_t	*it;

	if (!n || !ft_vi16_grow(self, n))
		return (NULL);
	it = ft_vi16_begin(self);
	if ((len = ft_vi16_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int16_t));
	self->len += n;
	return (it);
}

inline int32_t	*ft_vi32_unshiftn(t_vi32 *self, size_t n)
{
	size_t	len;
	int32_t	*it;

	if (!n || !ft_vi32_grow(self, n))
		return (NULL);
	it = ft_vi32_begin(self);
	if ((len = ft_vi32_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int32_t));
	self->len += n;
	return (it);
}

inline int64_t	*ft_vi64_unshiftn(t_vi64 *self, size_t n)
{
	size_t	len;
	int64_t	*it;

	if (!n || !ft_vi64_grow(self, n))
		return (NULL);
	it = ft_vi64_begin(self);
	if ((len = ft_vi64_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int64_t));
	self->len += n;
	return (it);
}

inline char		**ft_vstr_unshiftn(t_vstr *self, size_t n)
{
	size_t	len;
	char	**it;

	if (!n || !ft_vstr_grow(self, n))
		return (NULL);
	it = ft_vstr_begin(self);
	if ((len = ft_vstr_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(char *));
	self->len += n;
	return (it);
}
