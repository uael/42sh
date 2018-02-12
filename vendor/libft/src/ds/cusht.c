/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cusht.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqcusht(t_deq *self, void *item)
{
	return (ft_memcpy(ft_dequsht(self), item, self->isz));
}

inline char	*ft_sdscusht(t_sds *self, char item)
{
	char *it;

	it = ft_sdsusht(self);
	*it = item;
	return (it);
}

inline void	*ft_veccusht(t_vec *self, void *item)
{
	return (ft_memcpy(ft_vecusht(self), item, self->isz));
}
