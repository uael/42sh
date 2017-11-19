/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_shiftn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline t_bool	ft_vu8_shift(t_vu8 *self, uint8_t *out)
{
	return ((t_bool)(ft_vu8_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_vu16_shift(t_vu16 *self, uint16_t *out)
{
	return ((t_bool)(ft_vu16_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_vu32_shift(t_vu32 *self, uint32_t *out)
{
	return ((t_bool)(ft_vu32_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_vu64_shift(t_vu64 *self, uint64_t *out)
{
	return ((t_bool)(ft_vu64_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_vec_shift(t_vec *self, void *out)
{
	return ((t_bool)(ft_vec_shiftn(self, 1, out) == 1));
}
