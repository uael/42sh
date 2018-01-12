/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqpush(t_deq *self)
{
	return (ft_deqnpush(self, 1));
}

inline char	*ft_sdspush(t_sds *self)
{
	return (ft_sdsnpush(self, 1));
}

inline void	*ft_vecpush(t_vec *self)
{
	return (ft_vecnpush(self, 1));
}
