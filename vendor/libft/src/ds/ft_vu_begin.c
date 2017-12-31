/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vu_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline uint8_t	*ft_vu8_begin(t_vu8 *self)
{
	return (self->buf);
}

inline uint16_t	*ft_vu16_begin(t_vu16 *self)
{
	return (self->buf);
}

inline uint32_t	*ft_vu32_begin(t_vu32 *self)
{
	return (self->buf);
}

inline uint64_t	*ft_vu64_begin(t_vu64 *self)
{
	return (self->buf);
}

inline void		*ft_vec_begin(t_vec *self)
{
	return (self->buf);
}
