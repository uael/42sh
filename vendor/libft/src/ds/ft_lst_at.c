/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:26:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/lst.h"

inline t_node	*ft_lst_front(t_lst *self)
{
	return (self->next);
}

inline t_node	*ft_lst_back(t_lst *self)
{
	return (self->prev);
}

inline t_node	*ft_lst_at(t_lst *self, size_t n)
{
	return (ft_node_next(ft_lst_front(self), n));
}

inline t_node	*ft_lst_rat(t_lst *self, size_t n)
{
	return (ft_node_prev(ft_lst_back(self), n));
}
