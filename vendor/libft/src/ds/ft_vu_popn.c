/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_popn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline size_t	ft_vu8_popn(t_vu8 *self, size_t n, uint8_t *out)
{
	size_t len;

	if ((len = ft_vu8_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vu8_end(self), n * sizeof(uint8_t));
		return (n);
	}
}

inline size_t	ft_vu16_popn(t_vu16 *self, size_t n, uint16_t *out)
{
	size_t len;

	if ((len = ft_vu16_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vu16_end(self), n * sizeof(uint16_t));
		return (n);
	}
}

inline size_t	ft_vu32_popn(t_vu32 *self, size_t n, uint32_t *out)
{
	size_t len;

	if ((len = ft_vu32_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vu32_end(self), n * sizeof(uint32_t));
		return (n);
	}
}

inline size_t	ft_vu64_popn(t_vu64 *self, size_t n, uint64_t *out)
{
	size_t len;

	if ((len = ft_vu64_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vu64_end(self), n * sizeof(uint64_t));
		return (n);
	}
}

inline size_t	ft_vec_popn(t_vec *self, size_t n, void *out)
{
	size_t len;

	if ((len = ft_vec_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vec_end(self), n * self->isz);
		return (n);
	}
}
