/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 18:02:00 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqcpush(t_deq *self, void *item)
{
	return (ft_memcpy(ft_deqnpush(self, 1), item, self->isz));
}

inline char	*ft_sdscpush(t_sds *self, char item)
{
	char *it;

	it = ft_sdsnpush(self, 1);
	*it = item;
	return (it);
}

inline void	*ft_veccpush(t_vec *self, void *item)
{
	return (ft_memcpy(ft_vecnpush(self, 1), item, self->isz));
}
