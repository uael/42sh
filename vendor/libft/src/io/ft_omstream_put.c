/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omstream_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 11:24:33 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/omstream.h"

inline t_bool	ft_omstream_putc(t_omstream *self, char c)
{
	return (ft_omstream_write(self, &c, 1) == 1 ? TRUE : FALSE);
}

inline size_t	ft_omstream_puts(t_omstream *self, char const *s)
{
	return (ft_omstream_write(self, s, ft_strlen(s)));
}

inline size_t	ft_omstream_putl(t_omstream *self, char const *s)
{
	return (ft_omstream_write(self, s, ft_strlen(s)) +
		ft_omstream_putc(self, '\n'));
}

inline void		ft_omstream_clear(t_omstream *self)
{
	self->len = 0;
	self->cur = 0;
}
