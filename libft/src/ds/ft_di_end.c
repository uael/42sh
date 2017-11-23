/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:32:41 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_end(t_di8 *self)
{
	return (self->buf + self->len);
}

inline int16_t	*ft_di16_end(t_di16 *self)
{
	return (self->buf + self->len);
}

inline int32_t	*ft_di32_end(t_di32 *self)
{
	return (self->buf + self->len);
}

inline int64_t	*ft_di64_end(t_di64 *self)
{
	return (self->buf + self->len);
}

inline char		**ft_dqstr_end(t_dqstr *self)
{
	return (self->buf + self->len);
}
