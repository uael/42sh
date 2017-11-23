/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_popn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_du8_pop(t_du8 *self, uint8_t *out)
{
	return ((t_bool)(ft_du8_popn(self, 1, out) == 1));
}

inline t_bool	ft_du16_pop(t_du16 *self, uint16_t *out)
{
	return ((t_bool)(ft_du16_popn(self, 1, out) == 1));
}

inline t_bool	ft_du32_pop(t_du32 *self, uint32_t *out)
{
	return ((t_bool)(ft_du32_popn(self, 1, out) == 1));
}

inline t_bool	ft_du64_pop(t_du64 *self, uint64_t *out)
{
	return ((t_bool)(ft_du64_popn(self, 1, out) == 1));
}

inline t_bool	ft_deq_pop(t_deq *self, void *out)
{
	return ((t_bool)(ft_deq_popn(self, 1, out) == 1));
}
