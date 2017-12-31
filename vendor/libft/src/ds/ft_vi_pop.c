/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_popn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline t_bool	ft_vi8_pop(t_vi8 *self, int8_t *out)
{
	return ((t_bool)(ft_vi8_popn(self, 1, out) == 1));
}

inline t_bool	ft_vi16_pop(t_vi16 *self, int16_t *out)
{
	return ((t_bool)(ft_vi16_popn(self, 1, out) == 1));
}

inline t_bool	ft_vi32_pop(t_vi32 *self, int32_t *out)
{
	return ((t_bool)(ft_vi32_popn(self, 1, out) == 1));
}

inline t_bool	ft_vi64_pop(t_vi64 *self, int64_t *out)
{
	return ((t_bool)(ft_vi64_popn(self, 1, out) == 1));
}

inline t_bool	ft_vstr_pop(t_vstr *self, char **out)
{
	return ((t_bool)(ft_vstr_popn(self, 1, out) == 1));
}
