/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ostream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:21:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ostream.h"

static char			g_cout_buf[FT_PAGE_SIZE];

static t_ostream	g_cout_pvt =
{
	OSTREAM_FILE, { { NULL, STDOUT_FILENO, g_cout_buf, 0, 0, 0, 0 } }
};

t_ostream			*g_cout = &g_cout_pvt;

inline int			ft_ostream_open(t_ostream *self, char const *filename)
{
	self->kind = OSTREAM_FILE;
	return (ft_ofstream_open(&self->u.file, filename));
}

inline void			ft_ostream_mopen(t_ostream *self)
{
	self->kind = OSTREAM_MEM;
	return (ft_omstream_open(&self->u.mem));
}

inline int			ft_ostream_close(t_ostream *self)
{
	if (self->kind == OSTREAM_FILE)
		return (ft_ofstream_close(&self->u.file));
	ft_omstream_close(&self->u.mem);
	return (YEP);
}
