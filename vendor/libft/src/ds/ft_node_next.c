/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:26:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/lst.h"

static inline t_node	*node_next_5(t_node *node, size_t n)
{
	while (n--)
		node = node->next->next->next->next->next;
	return (node);
}

static inline t_node	*node_next_4(t_node *node, size_t n)
{
	while (n--)
		node = node->next->next->next->next;
	return (node);
}

static inline t_node	*node_next_3(t_node *node, size_t n)
{
	while (n--)
		node = node->next->next->next;
	return (node);
}

static inline t_node	*node_next_2(t_node *node, size_t n)
{
	while (n--)
		node = node->next->next;
	return (node);
}

inline t_node			*ft_node_next(t_node *self, size_t n)
{
	if (!n)
		return (self);
	if (!(n % 5))
		return (node_next_5(self, n / 5));
	if (!(n % 4))
		return (node_next_4(self, n / 4));
	if (!(n % 3))
		return (node_next_3(self, n / 3));
	if (!(n % 2))
		return (node_next_2(self, n / 2));
	while (n--)
		self = self->next;
	return (self);
}
