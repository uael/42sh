/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ostream_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:50:09 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ostream.h"

inline t_sz	ft_ostream_putc(t_ostream *self, char c)
{
	if (self->kind == OSTREAM_FILE)
		return (ft_ofstream_putc(&self->u.file, c));
	return (ft_omstream_putc(&self->u.mem, c));
}

inline t_sz	ft_ostream_puts(t_ostream *self, char const *s)
{
	if (self->kind == OSTREAM_FILE)
		return (ft_ofstream_puts(&self->u.file, s));
	return (ft_omstream_puts(&self->u.mem, s));
}
