/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:21:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/istream.h"

static t_istream	g_cin_pvt =
{
	ISTREAM_FILE, { { NULL, STDIN_FILENO, NULL, 0, 0, 0, 0, 0 } }
};

t_istream			*g_cin = &g_cin_pvt;

inline int			ft_istream_open(t_istream *self, char const *filename)
{
	self->kind = ISTREAM_FILE;
	return (ft_ifstream_open(&self->u.file, filename));
}

inline void			ft_istream_mopen(t_istream *self, char const *str)
{
	self->kind = ISTREAM_MEM;
	return (ft_imstream_open(&self->u.mem, str));
}

inline void			ft_istream_mnopen(t_istream *s, char const *str, size_t n)
{
	s->kind = ISTREAM_MEM;
	return (ft_imstream_nopen(&s->u.mem, str, n));
}

inline int			ft_istream_close(t_istream *self)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_close(&self->u.file));
	return (YEP);
}
