/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_end(t_du8 *self)
{
	return (self->buf + self->len);
}

inline uint16_t	*ft_du16_end(t_du16 *self)
{
	return (self->buf + self->len);
}

inline uint32_t	*ft_du32_end(t_du32 *self)
{
	return (self->buf + self->len);
}

inline uint64_t	*ft_du64_end(t_du64 *self)
{
	return (self->buf + self->len);
}

inline void		*ft_deq_end(t_deq *self)
{
	return ((char *)self->buf + (self->len * self->isz));
}
