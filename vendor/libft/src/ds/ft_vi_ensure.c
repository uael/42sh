/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_ensure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline t_bool	ft_vi8_ensure(t_vi8 *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vi8_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vi8_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_vi16_ensure(t_vi16 *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vi16_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vi16_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_vi32_ensure(t_vi32 *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vi32_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vi32_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_vi64_ensure(t_vi64 *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vi64_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vi64_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_vstr_ensure(t_vstr *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vstr_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vstr_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}
