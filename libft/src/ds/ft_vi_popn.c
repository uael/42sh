/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_popn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline size_t	ft_vi8_popn(t_vi8 *self, size_t n, int8_t *out)
{
	size_t len;

	if ((len = ft_vi8_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vi8_end(self), n * sizeof(int8_t));
		return (n);
	}
}

inline size_t	ft_vi16_popn(t_vi16 *self, size_t n, int16_t *out)
{
	size_t len;

	if ((len = ft_vi16_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vi16_end(self), n * sizeof(int16_t));
		return (n);
	}
}

inline size_t	ft_vi32_popn(t_vi32 *self, size_t n, int32_t *out)
{
	size_t len;

	if ((len = ft_vi32_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vi32_end(self), n * sizeof(int32_t));
		return (n);
	}
}

inline size_t	ft_vi64_popn(t_vi64 *self, size_t n, int64_t *out)
{
	size_t len;

	if ((len = ft_vi64_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vi64_end(self), n * sizeof(int64_t));
		return (n);
	}
}

inline size_t	ft_vstr_popn(t_vstr *self, size_t n, char **out)
{
	size_t len;

	if ((len = ft_vstr_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vstr_end(self), n * sizeof(char *));
		return (n);
	}
}
