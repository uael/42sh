/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/lst.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/15 18:23:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_LST_H
# define LIBFT_DS_LST_H

# include "../str.h"
# include "../lib.h"
# include "../math.h"

typedef struct	s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	void			*val;
}				t_node;

extern t_node	*ft_node_ctor(t_node *self);
extern t_node	*ft_node_new(void *val);
extern t_node	*ft_node_link(t_node *node, t_node *prev, t_node *next);
extern t_node	*ft_node_unlink(t_node *self, t_node *prev, t_node *next);
extern t_node	*ft_node_push(t_node *self, void *val);
extern t_node	*ft_node_unshift(t_node *self, void *val);
extern t_node	*ft_node_next(t_node *self, size_t n);
extern t_node	*ft_node_prev(t_node *self, size_t n);

typedef struct	s_lst
{
	t_node	*prev;
	t_node	*next;
	size_t	size;
}				t_lst;

extern t_lst	*ft_lst_ctor(t_lst *self);
extern t_node	*ft_lst_front(t_lst *self);
extern t_node	*ft_lst_back(t_lst *self);
extern t_node	*ft_lst_at(t_lst *self, size_t n);
extern t_node	*ft_lst_rat(t_lst *self, size_t n);
extern t_lst	*ft_lst_push(t_lst *self, void *val);

#endif
