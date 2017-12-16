/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_popn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_di8_pop(t_di8 *self, int8_t *out)
{
	return ((t_bool)(ft_di8_popn(self, 1, out) == 1));
}

inline t_bool	ft_di16_pop(t_di16 *self, int16_t *out)
{
	return ((t_bool)(ft_di16_popn(self, 1, out) == 1));
}

inline t_bool	ft_di32_pop(t_di32 *self, int32_t *out)
{
	return ((t_bool)(ft_di32_popn(self, 1, out) == 1));
}

inline t_bool	ft_di64_pop(t_di64 *self, int64_t *out)
{
	return ((t_bool)(ft_di64_popn(self, 1, out) == 1));
}

inline t_bool	ft_dqstr_pop(t_dqstr *self, char **out)
{
	return ((t_bool)(ft_dqstr_popn(self, 1, out) == 1));
}
