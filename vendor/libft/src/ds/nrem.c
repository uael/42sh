/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nrem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline size_t	ft_deqnrem(t_deq *s, size_t i, size_t n, void *out)
{
	size_t	len;
	char	*it;

	if (i >= (len = ft_deqlen(s)))
		return (0);
	else if (i == len - 1)
		return (ft_deqnpop(s, n, out));
	else if (i == 0)
		return (ft_deqnsht(s, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_deqat(s, i);
		if (out)
			ft_memcpy(out, it, n * s->isz);
		len = len - i - n + 1;
		ft_memmove(it, it + (n * s->isz), len * s->isz);
		s->len -= n;
		return (n);
	}
}

inline size_t	ft_sdsnrem(t_sds *self, size_t idx, size_t n, char *out)
{
	size_t	len;
	char	*it;

	if (idx >= (len = ft_sdslen(self)))
		return (0);
	else if (idx == len - 1)
		return (ft_sdsnpop(self, n, out));
	else if (idx == 0)
		return (ft_sdsnsht(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_sdsat(self, idx);
		if (out)
			ft_memcpy(out, it, n * sizeof(char));
		ft_memmove(it, it + n, (len - idx - n + 1) * sizeof(char));
		self->len -= n;
		return (n);
	}
}

inline size_t	ft_vecnrem(t_vec *s, size_t i, size_t n, void *out)
{
	size_t	len;
	char	*it;

	if (i >= (len = ft_veclen(s)))
		return (0);
	else if (i == len - 1)
		return (ft_vecnpop(s, n, out));
	else if (i == 0)
		return (ft_vecnsht(s, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_vecat(s, i);
		if (out)
			ft_memcpy(out, it, n * s->isz);
		len = len - i - n + 1;
		ft_memmove(it, it + (n * s->isz), len * s->isz);
		s->len -= n;
		return (n);
	}
}
