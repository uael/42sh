/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_end(t_vu8 *self)
{
	return (self->buf + self->len);
}

inline uint16_t	*ft_vu16_end(t_vu16 *self)
{
	return (self->buf + self->len);
}

inline uint32_t	*ft_vu32_end(t_vu32 *self)
{
	return (self->buf + self->len);
}

inline uint64_t	*ft_vu64_end(t_vu64 *self)
{
	return (self->buf + self->len);
}

inline void		*ft_vec_end(t_vec *self)
{
	return ((char *)self->buf + (self->len * self->isz));
}
