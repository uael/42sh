/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_shiftn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:31:13 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_di8_shiftn(t_di8 *self, size_t n, int8_t *out)
{
	size_t	len;
	int8_t	*it;

	if (!n || (len = ft_di8_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_di8_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int8_t));
	self->cur += n;
	return (n);
}

inline size_t	ft_di16_shiftn(t_di16 *self, size_t n, int16_t *out)
{
	size_t	len;
	int16_t	*it;

	if (!n || (len = ft_di16_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_di16_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int16_t));
	self->cur += n;
	return (n);
}

inline size_t	ft_di32_shiftn(t_di32 *self, size_t n, int32_t *out)
{
	size_t	len;
	int32_t	*it;

	if (!n || (len = ft_di32_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_di32_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int32_t));
	self->cur += n;
	return (n);
}

inline size_t	ft_di64_shiftn(t_di64 *self, size_t n, int64_t *out)
{
	size_t	len;
	int64_t	*it;

	if (!n || (len = ft_di64_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_di64_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int64_t));
	self->cur += n;
	return (n);
}

inline size_t	ft_dqstr_shiftn(t_dqstr *self, size_t n, char **out)
{
	size_t	len;
	char	**it;

	if (!n || (len = ft_dqstr_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_dqstr_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(int64_t));
	self->cur += n;
	return (n);
}
