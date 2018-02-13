/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 19:37:37 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqback(t_deq *self)
{
	return ((char *)self->buf + (((self->len ? self->len - 1 : 0) + self->cur)
		* self->isz));
}

inline char	*ft_sdsback(t_sds *self)
{
	return (self->buf + (self->len ? self->len - 1 : 0));
}

inline void	*ft_vecback(t_vec *self)
{
	return ((char *)self->buf + ((self->len ? self->len - 1 : 0) * self->isz));
}
