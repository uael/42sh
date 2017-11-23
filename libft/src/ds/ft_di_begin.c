/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:26:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_begin(t_di8 *self)
{
	return (self->buf);
}

inline int16_t	*ft_di16_begin(t_di16 *self)
{
	return (self->buf);
}

inline int32_t	*ft_di32_begin(t_di32 *self)
{
	return (self->buf);
}

inline int64_t	*ft_di64_begin(t_di64 *self)
{
	return (self->buf);
}

inline char		**ft_dqstr_begin(t_dqstr *self)
{
	return (self->buf);
}
