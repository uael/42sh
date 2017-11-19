/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_shiftn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline t_bool	ft_vi8_shift(t_vi8 *self, int8_t *out)
{
	return ((t_bool)(ft_vi8_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_vi16_shift(t_vi16 *self, int16_t *out)
{
	return ((t_bool)(ft_vi16_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_vi32_shift(t_vi32 *self, int32_t *out)
{
	return ((t_bool)(ft_vi32_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_vi64_shift(t_vi64 *self, int64_t *out)
{
	return ((t_bool)(ft_vi64_shiftn(self, 1, out) == 1));
}

inline t_bool	ft_vstr_shift(t_vstr *self, char **out)
{
	return ((t_bool)(ft_vstr_shiftn(self, 1, out) == 1));
}
