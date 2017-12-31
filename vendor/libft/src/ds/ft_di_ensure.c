/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_ensure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:31:14 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_di8_ensure(t_di8 *self, size_t n)
{
	if (++n < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_di8_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_di8_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_di16_ensure(t_di16 *self, size_t n)
{
	if (++n < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_di16_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_di16_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_di32_ensure(t_di32 *self, size_t n)
{
	if (++n < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_di32_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_di32_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_di64_ensure(t_di64 *self, size_t n)
{
	if (++n < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_di64_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_di64_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_dqstr_ensure(t_dqstr *self, size_t n)
{
	if (++n < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_dqstr_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_dqstr_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}
