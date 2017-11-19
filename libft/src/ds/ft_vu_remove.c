/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline t_bool	ft_vu8_remove(t_vu8 *self, size_t idx, uint8_t *out)
{
	return ((t_bool)(ft_vu8_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_vu16_remove(t_vu16 *self, size_t idx, uint16_t *out)
{
	return ((t_bool)(ft_vu16_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_vu32_remove(t_vu32 *self, size_t idx, uint32_t *out)
{
	return ((t_bool)(ft_vu32_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_vu64_remove(t_vu64 *self, size_t idx, uint64_t *out)
{
	return ((t_bool)(ft_vu64_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_vec_remove(t_vec *self, size_t idx, void *out)
{
	return ((t_bool)(ft_vec_removen(self, idx, 1, out) == 1));
}
