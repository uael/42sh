/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usht.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_dequsht(t_deq *self)
{
	return (ft_deqnusht(self, 1));
}

inline char	*ft_sdsusht(t_sds *self)
{
	return (ft_sdsnusht(self, 1));
}

inline void	*ft_vecusht(t_vec *self)
{
	return (ft_vecnusht(self, 1));
}
