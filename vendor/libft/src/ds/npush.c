/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:04:53 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqnpush(t_deq *self, size_t n)
{
	uint64_t *it;

	ft_deqgrow(self, n);
	it = ft_deqend(self);
	self->len += n;
	return (it);
}

inline char	*ft_sdsnpush(t_sds *self, size_t n)
{
	char *it;

	ft_sdsgrow(self, n);
	it = ft_sdsend(self);
	self->len += n;
	it[n] = '\0';
	return (it);
}

inline void	*ft_vecnpush(t_vec *self, size_t n)
{
	void *it;

	ft_vecgrow(self, n);
	it = ft_vecend(self);
	self->len += n;
	return (it);
}
