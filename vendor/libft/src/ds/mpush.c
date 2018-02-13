/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncpush.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqmpush(t_deq *self, void const *items, size_t n)
{
	return (ft_memcpy(ft_deqnpush(self, n), items, n * self->isz));
}

inline char	*ft_sdsmpush(t_sds *self, char const *items, size_t n)
{
	return (ft_memcpy(ft_sdsnpush(self, n), items, n * sizeof(char)));
}

inline void	*ft_vecmpush(t_vec *self, void const *items, size_t n)
{
	return (ft_memcpy(ft_vecnpush(self, n), items, n * self->isz));
}
