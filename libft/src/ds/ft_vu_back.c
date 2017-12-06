/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 19:37:37 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_back(t_vu8 *self)
{

	return (self->buf + (self->len ? self->len - 1 : 0));
}

inline uint16_t	*ft_vu16_back(t_vu16 *self)
{
	return (self->buf + (self->len ? self->len - 1 : 0));
}

inline uint32_t	*ft_vu32_back(t_vu32 *self)
{
	return (self->buf + (self->len ? self->len - 1 : 0));
}

inline uint64_t	*ft_vu64_back(t_vu64 *self)
{
	return (self->buf + (self->len ? self->len - 1 : 0));
}

inline void		*ft_vec_back(t_vec *self)
{
	return ((char *)self->buf + ((self->len ? self->len - 1 : 0) * self->isz));
}
