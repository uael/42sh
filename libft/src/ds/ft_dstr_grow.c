/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_grow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline t_bool	ft_dstr_grow(t_dstr *self, size_t n)
{
	if ((n += self->len + 1) < FT_DSTR_MIN_CAP && FT_DSTR_MIN_CAP > self->cap)
		return (ft_dstr_realloc(self, FT_DSTR_MIN_CAP));
	else if (n > self->cap)
		return (ft_dstr_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}
