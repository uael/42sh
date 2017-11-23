/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_di8_remove(t_di8 *self, size_t idx, int8_t *out)
{
	return ((t_bool)(ft_di8_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_di16_remove(t_di16 *self, size_t idx, int16_t *out)
{
	return ((t_bool)(ft_di16_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_di32_remove(t_di32 *self, size_t idx, int32_t *out)
{
	return ((t_bool)(ft_di32_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_di64_remove(t_di64 *self, size_t idx, int64_t *out)
{
	return ((t_bool)(ft_di64_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_dqstr_remove(t_dqstr *self, size_t idx, char **out)
{
	return ((t_bool)(ft_dqstr_removen(self, idx, 1, out) == 1));
}
