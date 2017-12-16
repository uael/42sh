/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_popn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_du8_popn(t_du8 *self, size_t n, uint8_t *out)
{
	size_t len;

	if ((len = ft_du8_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_du8_end(self), n * sizeof(uint8_t));
		return (n);
	}
}

inline size_t	ft_du16_popn(t_du16 *self, size_t n, uint16_t *out)
{
	size_t len;

	if ((len = ft_du16_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_du16_end(self), n * sizeof(uint16_t));
		return (n);
	}
}

inline size_t	ft_du32_popn(t_du32 *self, size_t n, uint32_t *out)
{
	size_t len;

	if ((len = ft_du32_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_du32_end(self), n * sizeof(uint32_t));
		return (n);
	}
}

inline size_t	ft_du64_popn(t_du64 *self, size_t n, uint64_t *out)
{
	size_t len;

	if ((len = ft_du64_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_du64_end(self), n * sizeof(uint64_t));
		return (n);
	}
}

inline size_t	ft_deq_popn(t_deq *self, size_t n, void *out)
{
	size_t len;

	if ((len = ft_deq_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_deq_end(self), n * self->isz);
		return (n);
	}
}
