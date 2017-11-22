/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istream_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/istream.h"

inline ssize_t			ft_istream_get(t_istream *self, char *buf, size_t n)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_get(&self->u.file, buf, n));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_get(&self->u.mem, buf, n));
	return (RET_ERR);
}

inline t_ret			ft_istream_peek(t_istream *self, char *c, size_t n)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_peek(&self->u.file, c, n));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_peek(&self->u.mem, c, n));
	return (RET_ERR);
}
