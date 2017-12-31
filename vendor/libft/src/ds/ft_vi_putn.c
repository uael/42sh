/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_putn(t_vi8 *self, size_t idx, size_t n)
{
	size_t	len;
	int8_t	*it;

	if (idx == 0)
		return (ft_vi8_unshiftn(self, n));
	else if (idx == (len = ft_vi8_size(self)))
		return (ft_vi8_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vi8_grow(self, n);
		it = ft_vi8_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int8_t));
		self->len += n;
		return (it);
	}
}

inline int16_t	*ft_vi16_putn(t_vi16 *self, size_t idx, size_t n)
{
	size_t	len;
	int16_t	*it;

	if (idx == 0)
		return (ft_vi16_unshiftn(self, n));
	else if (idx == (len = ft_vi16_size(self)))
		return (ft_vi16_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vi16_grow(self, n);
		it = ft_vi16_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int16_t));
		self->len += n;
		return (it);
	}
}

inline int32_t	*ft_vi32_putn(t_vi32 *self, size_t idx, size_t n)
{
	size_t	len;
	int32_t	*it;

	if (idx == 0)
		return (ft_vi32_unshiftn(self, n));
	else if (idx == (len = ft_vi32_size(self)))
		return (ft_vi32_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vi32_grow(self, n);
		it = ft_vi32_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int32_t));
		self->len += n;
		return (it);
	}
}

inline int64_t	*ft_vi64_putn(t_vi64 *self, size_t idx, size_t n)
{
	size_t	len;
	int64_t	*it;

	if (idx == 0)
		return (ft_vi64_unshiftn(self, n));
	else if (idx == (len = ft_vi64_size(self)))
		return (ft_vi64_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vi64_grow(self, n);
		it = ft_vi64_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(int64_t));
		self->len += n;
		return (it);
	}
}

inline char		**ft_vstr_putn(t_vstr *self, size_t idx, size_t n)
{
	size_t	len;
	char	**it;

	if (idx == 0)
		return (ft_vstr_unshiftn(self, n));
	else if (idx == (len = ft_vstr_size(self)))
		return (ft_vstr_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vstr_grow(self, n);
		it = ft_vstr_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(char *));
		self->len += n;
		return (it);
	}
}
