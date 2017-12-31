/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline t_bool	ft_deqrem(t_deq *self, size_t idx, void *out)
{
	return ((t_bool)(ft_deqnrem(self, idx, 1, out) == 1));
}

inline t_bool	ft_sdsrem(t_sds *self, size_t idx, char *out)
{
	return ((t_bool)(ft_sdsnrem(self, idx, 1, out) == 1));
}

inline t_bool	ft_vecrem(t_vec *self, size_t idx, void *out)
{
	return ((t_bool)(ft_vecnrem(self, idx, 1, out) == 1));
}
