/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istream_peek.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/istream.h"

inline void		ft_istream_flush(t_istream *self)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_flush(&self->u.file));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_flush(&self->u.mem));
}

inline int		ft_istream_rewind(t_istream *self, size_t n)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_rewind(&self->u.file, n));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_rewind(&self->u.mem, n));
	return (RET_ERR);
}

inline int		ft_istream_forward(t_istream *self, size_t n)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_forward(&self->u.file, n));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_forward(&self->u.mem, n));
	return (RET_ERR);
}

inline int		ft_istream_seek(t_istream *self, size_t off)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_seek(&self->u.file, off));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_seek(&self->u.mem, off));
	return (RET_ERR);
}

inline size_t	ft_istream_tell(t_istream const *self)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_tell(&self->u.file));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_tell(&self->u.mem));
	return (0);
}
