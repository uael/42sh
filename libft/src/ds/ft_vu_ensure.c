/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_ensure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline t_bool	ft_vu8_ensure(t_vu8 *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vu8_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vu8_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_vu16_ensure(t_vu16 *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vu16_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vu16_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_vu32_ensure(t_vu32 *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vu32_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vu32_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_vu64_ensure(t_vu64 *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vu64_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vu64_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_vec_ensure(t_vec *self, size_t n)
{
	if (++n < FT_VEC_MIN_CAP && FT_VEC_MIN_CAP > self->cap)
		return (ft_vec_realloc(self, FT_VEC_MIN_CAP));
	else if (n > self->cap)
		return (ft_vec_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}
