/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:26:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/lst.h"

inline t_node	*ft_node_ctor(t_node *self)
{
	FT_INIT(self, t_node);
	self->next = self;
	self->prev = self;
	return (self);
}

inline t_node	*ft_node_new(void *val)
{
	t_node *node;

	if (!(node = ft_calloc(sizeof(t_node))))
		return (NULL);
	node->val = val;
	return (node);
}

inline t_node	*ft_node_link(t_node *node, t_node *prev, t_node *next)
{
	node->next = prev->next;
	node->prev = next->prev;
	prev->next = node;
	next->prev = node;
	return (node);
}

inline t_node	*ft_node_unlink(t_node *self, t_node *prev, t_node *next)
{
	next->prev = prev;
	prev->next = next;
	self->prev = self;
	self->next = self;
	return (self);
}
