/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_removen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_di8_removen(t_di8 *self, size_t idx, size_t n, int8_t *out)
{
	size_t	len;
	int8_t	*it;

	if (idx >= (len = ft_di8_size(self)))
		return (0);
	else if (idx == len - 1)
		return (ft_di8_popn(self, n, out));
	else if (idx == 0)
		return (ft_di8_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_di8_at(self, idx);
		if (out)
			ft_memcpy(out, it, n * sizeof(int8_t));
		ft_memmove(it, it + n, (len - idx - n + 1) * sizeof(int8_t));
		return (n);
	}
}

inline size_t	ft_di16_removen(t_di16 *self, size_t i, size_t n, int16_t *out)
{
	size_t	len;
	int16_t	*it;

	if (i >= (len = ft_di16_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_di16_popn(self, n, out));
	else if (i == 0)
		return (ft_di16_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_di16_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(int16_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(int16_t));
		return (n);
	}
}

inline size_t	ft_di32_removen(t_di32 *self, size_t i, size_t n, int32_t *out)
{
	size_t	len;
	int32_t	*it;

	if (i >= (len = ft_di32_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_di32_popn(self, n, out));
	else if (i == 0)
		return (ft_di32_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_di32_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(int32_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(int32_t));
		return (n);
	}
}

inline size_t	ft_di64_removen(t_di64 *self, size_t i, size_t n, int64_t *out)
{
	size_t	len;
	int64_t	*it;

	if (i >= (len = ft_di64_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_di64_popn(self, n, out));
	else if (i == 0)
		return (ft_di64_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_di64_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(int64_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(int64_t));
		return (n);
	}
}

inline size_t	ft_dqstr_removen(t_dqstr *self, size_t i, size_t n, char **out)
{
	size_t	len;
	char	**it;

	if (i >= (len = ft_dqstr_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_dqstr_popn(self, n, out));
	else if (i == 0)
		return (ft_dqstr_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_dqstr_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(char *));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(char *));
		return (n);
	}
}
