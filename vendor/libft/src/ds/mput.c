/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mput.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqmput(t_deq *self, size_t idx, void const *buf, size_t n)
{
	return (ft_memcpy(ft_deqnput(self, idx, n), buf, n * self->isz));
}

inline char	*ft_sdsmput(t_sds *self, size_t idx, char const *buf, size_t n)
{
	return (ft_memcpy(ft_sdsnput(self, idx, n), buf, n * sizeof(char)));
}

inline void	*ft_vecmput(t_vec *self, size_t idx, void const *buf, size_t n)
{
	return (ft_memcpy(ft_vecnput(self, idx, n), buf, n * self->isz));
}
