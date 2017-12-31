/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:26:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/lst.h"

inline t_node	*ft_node_push(t_node *self, void *val)
{
	t_node *new;

	if (!(new = ft_node_new(val)))
		return (NULL);
	return (ft_node_link(new, self, self->next));
}

inline t_node	*ft_node_unshift(t_node *self, void *val)
{
	t_node *new;

	if (!(new = ft_node_new(val)))
		return (NULL);
	return (ft_node_link(new, self->prev, self));
}
