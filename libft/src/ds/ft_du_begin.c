/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:43:11 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_begin(t_du8 *self)
{
	return (self->buf + self->cur);
}

inline uint16_t	*ft_du16_begin(t_du16 *self)
{
	return (self->buf + self->cur);
}

inline uint32_t	*ft_du32_begin(t_du32 *self)
{
	return (self->buf + self->cur);
}

inline uint64_t	*ft_du64_begin(t_du64 *self)
{
	return (self->buf + self->cur);
}

inline void		*ft_deq_begin(t_deq *self)
{
	return (self->buf + (self->cur * self->isz));
}
