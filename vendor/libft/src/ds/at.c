/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqat(t_deq *self, size_t idx)
{
	return ((char *)ft_deqbeg(self) + (idx * self->isz));
}

inline char	*ft_sdsat(t_sds *self, size_t idx)
{
	return (ft_sdsbeg(self) + idx);
}

inline void	*ft_vecat(t_vec *self, size_t idx)
{
	return ((char *)ft_vecbeg(self) + (idx * self->isz));
}
