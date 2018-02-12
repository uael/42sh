/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musht.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqmusht(t_deq *self, void const *b, size_t n)
{
	return (ft_memcpy(ft_deqnusht(self, n), b, n * self->isz));
}

inline char	*ft_sdsmusht(t_sds *self, char const *items, size_t n)
{
	return (ft_memcpy(ft_sdsnusht(self, n), items, n * sizeof(char)));
}

inline void	*ft_vecmusht(t_vec *self, void const *b, size_t n)
{
	return (ft_memcpy(ft_vecnusht(self, n), b, n * self->isz));
}
