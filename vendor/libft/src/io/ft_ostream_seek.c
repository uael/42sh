/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ostream_peek.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ostream.h"

inline void		ft_ostream_flush(t_ostream *self)
{
	if (self->kind == OSTREAM_FILE)
		return (ft_ofstream_flush(&self->u.file));
}

inline int		ft_ostream_rewind(t_ostream *self, size_t n)
{
	if (self->kind == OSTREAM_FILE)
		return (ft_ofstream_rewind(&self->u.file, n));
	return (ft_omstream_rewind(&self->u.mem, n) ? YEP : NOP);
}

inline int		ft_ostream_forward(t_ostream *self, size_t n)
{
	if (self->kind == OSTREAM_FILE)
		return (ft_ofstream_forward(&self->u.file, n));
	return (ft_omstream_forward(&self->u.mem, n) ? YEP : NOP);
}

inline int		ft_ostream_seek(t_ostream *self, size_t off)
{
	if (self->kind == OSTREAM_FILE)
		return (ft_ofstream_seek(&self->u.file, off));
	return (ft_omstream_seek(&self->u.mem, off) ? YEP : NOP);
}

inline size_t	ft_ostream_tell(t_ostream const *self)
{
	if (self->kind == OSTREAM_FILE)
		return (ft_ofstream_tell(&self->u.file));
	return (ft_omstream_tell(&self->u.mem));
}
