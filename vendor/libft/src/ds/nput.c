/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nput.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:05:48 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqnput(t_deq *self, size_t idx, size_t n)
{
	size_t	len;
	void	*it;

	if (idx == 0)
		return (ft_deqnusht(self, n));
	else if (idx == (len = ft_deqlen(self)))
		return (ft_deqnpush(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_deqgrow(self, n);
		it = ft_deqat(self, idx);
		ft_memmove((char *)it + (n * self->isz), it,
			(len - idx + 1) * self->isz);
		self->len += n;
		return (it);
	}
}

inline char	*ft_sdsnput(t_sds *self, size_t idx, size_t n)
{
	size_t	len;
	char	*it;

	if (idx == 0)
		return (ft_sdsnusht(self, n));
	else if (idx == (len = ft_sdslen(self)))
		return (ft_sdsnpush(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_sdsgrow(self, n);
		it = ft_sdsbeg(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(char));
		self->len += n;
		return (it);
	}
}

inline void	*ft_vecnput(t_vec *self, size_t idx, size_t n)
{
	size_t	len;
	void	*it;

	if (idx == 0)
		return (ft_vecnusht(self, n));
	else if (idx == (len = ft_veclen(self)))
		return (ft_vecnpush(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_vecgrow(self, n);
		it = ft_vecat(self, idx);
		ft_memmove((char *)it + (n * self->isz), it,
			(len - idx + 1) * self->isz);
		self->len += n;
		return (it);
	}
}
