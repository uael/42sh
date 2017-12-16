/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_putn(t_di8 *self, size_t idx, size_t n)
{
	size_t	len;
	int8_t	*it;

	if (idx == 0)
		return (ft_di8_unshiftn(self, n));
	else if (idx == (len = ft_di8_size(self)))
		return (ft_di8_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_di8_grow(self, n);
		it = ft_di8_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int8_t));
		self->len += n;
		return (it);
	}
}

inline int16_t	*ft_di16_putn(t_di16 *self, size_t idx, size_t n)
{
	size_t	len;
	int16_t	*it;

	if (idx == 0)
		return (ft_di16_unshiftn(self, n));
	else if (idx == (len = ft_di16_size(self)))
		return (ft_di16_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_di16_grow(self, n);
		it = ft_di16_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int16_t));
		self->len += n;
		return (it);
	}
}

inline int32_t	*ft_di32_putn(t_di32 *self, size_t idx, size_t n)
{
	size_t	len;
	int32_t	*it;

	if (idx == 0)
		return (ft_di32_unshiftn(self, n));
	else if (idx == (len = ft_di32_size(self)))
		return (ft_di32_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_di32_grow(self, n);
		it = ft_di32_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int32_t));
		self->len += n;
		return (it);
	}
}

inline int64_t	*ft_di64_putn(t_di64 *self, size_t idx, size_t n)
{
	size_t	len;
	int64_t	*it;

	if (idx == 0)
		return (ft_di64_unshiftn(self, n));
	else if (idx == (len = ft_di64_size(self)))
		return (ft_di64_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_di64_grow(self, n);
		it = ft_di64_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int64_t));
		self->len += n;
		return (it);
	}
}

inline char		**ft_dqstr_putn(t_dqstr *self, size_t idx, size_t n)
{
	size_t	len;
	char	**it;

	if (idx == 0)
		return (ft_dqstr_unshiftn(self, n));
	else if (idx == (len = ft_dqstr_size(self)))
		return (ft_dqstr_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_dqstr_grow(self, n);
		it = ft_dqstr_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(char *));
		self->len += n;
		return (it);
	}
}
