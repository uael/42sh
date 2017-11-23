/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:31:14 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_du8_size(t_du8 *self)
{
	return (self->len - self->cur);
}

inline size_t	ft_du16_size(t_du16 *self)
{
	return (self->len - self->cur);
}

inline size_t	ft_du32_size(t_du32 *self)
{
	return (self->len - self->cur);
}

inline size_t	ft_du64_size(t_du64 *self)
{
	return (self->len - self->cur);
}

inline size_t	ft_deq_size(t_deq *self)
{
	return (self->len - self->cur);
}
