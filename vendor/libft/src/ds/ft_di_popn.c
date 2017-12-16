/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_popn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_di8_popn(t_di8 *self, size_t n, int8_t *out)
{
	size_t len;

	if ((len = ft_di8_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_di8_end(self), n * sizeof(int8_t));
		return (n);
	}
}

inline size_t	ft_di16_popn(t_di16 *self, size_t n, int16_t *out)
{
	size_t len;

	if ((len = ft_di16_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_di16_end(self), n * sizeof(int16_t));
		return (n);
	}
}

inline size_t	ft_di32_popn(t_di32 *self, size_t n, int32_t *out)
{
	size_t len;

	if ((len = ft_di32_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_di32_end(self), n * sizeof(int32_t));
		return (n);
	}
}

inline size_t	ft_di64_popn(t_di64 *self, size_t n, int64_t *out)
{
	size_t len;

	if ((len = ft_di64_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_di64_end(self), n * sizeof(int64_t));
		return (n);
	}
}

inline size_t	ft_dqstr_popn(t_dqstr *self, size_t n, char **out)
{
	size_t len;

	if ((len = ft_dqstr_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_dqstr_end(self), n * sizeof(char *));
		return (n);
	}
}
