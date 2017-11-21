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

inline char				ft_istream_getc(t_istream *self)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_getc(&self->u.file));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_getc(&self->u.mem));
	return ('\0');
}

inline ssize_t			ft_istream_get(t_istream *self, char *buf, size_t len)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_get(&self->u.file, buf, len));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_get(&self->u.mem, buf, len));
	return (-1);
}

inline char				ft_istream_peek(t_istream *self, size_t n)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_peek(&self->u.file, n));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_peek(&self->u.mem, n));
	return ('\0');
}
