/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_shiftn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_di8_shift(t_di8 *self, int8_t *out)
{
	return ((t_bool)(ft_di8_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_di16_shift(t_di16 *self, int16_t *out)
{
	return ((t_bool)(ft_di16_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_di32_shift(t_di32 *self, int32_t *out)
{
	return ((t_bool)(ft_di32_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_di64_shift(t_di64 *self, int64_t *out)
{
	return ((t_bool)(ft_di64_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_dqstr_shift(t_dqstr *self, char **out)
{
	return ((t_bool)(ft_dqstr_shiftn(self, 1, out) == 1));
}
