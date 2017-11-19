/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_shiftn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline size_t	ft_vi8_shiftn(t_vi8 *self, size_t n, int8_t *out)
{
	size_t	len;
	int8_t	*it;

	if (!n || (len = ft_vi8_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vi8_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int8_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int8_t));
	return (n);
}

inline size_t	ft_vi16_shiftn(t_vi16 *self, size_t n, int16_t *out)
{
	size_t	len;
	int16_t	*it;

	if (!n || (len = ft_vi16_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vi16_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int16_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int16_t));
	return (n);
}

inline size_t	ft_vi32_shiftn(t_vi32 *self, size_t n, int32_t *out)
{
	size_t	len;
	int32_t	*it;

	if (!n || (len = ft_vi32_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vi32_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int32_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int32_t));
	return (n);
}

inline size_t	ft_vi64_shiftn(t_vi64 *self, size_t n, int64_t *out)
{
	size_t	len;
	int64_t	*it;

	if (!n || (len = ft_vi64_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vi64_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int64_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int64_t));
	return (n);
}

inline size_t	ft_vstr_shiftn(t_vstr *self, size_t n, char **out)
{
	size_t	len;
	char	**it;

	if (!n || (len = ft_vstr_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_vstr_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int64_t));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int64_t));
	return (n);
}
