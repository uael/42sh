/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:31:13 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline size_t	ft_di8_size(t_di8 *self)
{
	return (self->len - self->cur);
}

inline size_t	ft_di16_size(t_di16 *self)
{
	return (self->len - self->cur);
}

inline size_t	ft_di32_size(t_di32 *self)
{
	return (self->len - self->cur);
}

inline size_t	ft_di64_size(t_di64 *self)
{
	return (self->len - self->cur);
}

inline size_t	ft_dqstr_size(t_dqstr *self)
{
	return (self->len - self->cur);
}
