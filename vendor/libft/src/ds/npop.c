/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline size_t	ft_deqnpop(t_deq *self, size_t n, void *out)
{
	size_t len;

	if ((len = ft_deqlen(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_deqend(self), n * self->isz);
		return (n);
	}
}

inline size_t	ft_sdsnpop(t_sds *self, size_t n, char *out)
{
	size_t	len;
	char	*it;

	if ((len = ft_sdslen(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		it = ft_sdsend(self);
		if (out)
			ft_memcpy(out, it, n * sizeof(char));
		*it = '\0';
		return (n);
	}
}

inline size_t	ft_vecnpop(t_vec *self, size_t n, void *out)
{
	size_t len;

	if ((len = ft_veclen(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		if (out)
			ft_memcpy(out, ft_vecend(self), n * self->isz);
		return (n);
	}
}
