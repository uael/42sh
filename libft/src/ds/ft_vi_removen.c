/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_removen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline size_t	ft_vi8_removen(t_vi8 *self, size_t idx, size_t n, int8_t *out)
{
	size_t	len;
	int8_t	*it;

	if (idx >= (len = ft_vi8_size(self)))
		return (0);
	else if (idx == len - 1)
		return (ft_vi8_popn(self, n, out));
	else if (idx == 0)
		return (ft_vi8_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vi8_at(self, idx);
		if (out)
			ft_memcpy(out, it, n * sizeof(int8_t));
		ft_memmove(it, it + n, (len - idx - n + 1) * sizeof(int8_t));
		return (n);
	}
}

inline size_t	ft_vi16_removen(t_vi16 *self, size_t i, size_t n, int16_t *out)
{
	size_t	len;
	int16_t	*it;

	if (i >= (len = ft_vi16_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_vi16_popn(self, n, out));
	else if (i == 0)
		return (ft_vi16_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vi16_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(int16_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(int16_t));
		return (n);
	}
}

inline size_t	ft_vi32_removen(t_vi32 *self, size_t i, size_t n, int32_t *out)
{
	size_t	len;
	int32_t	*it;

	if (i >= (len = ft_vi32_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_vi32_popn(self, n, out));
	else if (i == 0)
		return (ft_vi32_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vi32_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(int32_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(int32_t));
		return (n);
	}
}

inline size_t	ft_vi64_removen(t_vi64 *self, size_t i, size_t n, int64_t *out)
{
	size_t	len;
	int64_t	*it;

	if (i >= (len = ft_vi64_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_vi64_popn(self, n, out));
	else if (i == 0)
		return (ft_vi64_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vi64_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(int64_t));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(int64_t));
		return (n);
	}
}

inline size_t	ft_vstr_removen(t_vstr *self, size_t i, size_t n, char **out)
{
	size_t	len;
	char	**it;

	if (i >= (len = ft_vstr_size(self)))
		return (0);
	else if (i == len - 1)
		return (ft_vstr_popn(self, n, out));
	else if (i == 0)
		return (ft_vstr_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vstr_at(self, i);
		if (out)
			ft_memcpy(out, it, n * sizeof(char *));
		ft_memmove(it, it + n, (len - i - n + 1) * sizeof(char *));
		return (n);
	}
}
