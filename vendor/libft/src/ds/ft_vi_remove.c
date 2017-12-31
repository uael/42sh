/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline t_bool	ft_vi8_remove(t_vi8 *self, size_t idx, int8_t *out)
{
	return ((t_bool)(ft_vi8_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_vi16_remove(t_vi16 *self, size_t idx, int16_t *out)
{
	return ((t_bool)(ft_vi16_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_vi32_remove(t_vi32 *self, size_t idx, int32_t *out)
{
	return ((t_bool)(ft_vi32_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_vi64_remove(t_vi64 *self, size_t idx, int64_t *out)
{
	return ((t_bool)(ft_vi64_removen(self, idx, 1, out) == 1));
}

inline t_bool	ft_vstr_remove(t_vstr *self, size_t idx, char **out)
{
	return ((t_bool)(ft_vstr_removen(self, idx, 1, out) == 1));
}
