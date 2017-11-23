/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_du8_remove(t_du8 *self, size_t idx, uint8_t *out)
{
	return ((t_bool)(ft_du8_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_du16_remove(t_du16 *self, size_t idx, uint16_t *out)
{
	return ((t_bool)(ft_du16_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_du32_remove(t_du32 *self, size_t idx, uint32_t *out)
{
	return ((t_bool)(ft_du32_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_du64_remove(t_du64 *self, size_t idx, uint64_t *out)
{
	return ((t_bool)(ft_du64_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_deq_remove(t_deq *self, size_t idx, void *out)
{
	return ((t_bool)(ft_deq_removen(self, idx, 1, out) == 1));
}
