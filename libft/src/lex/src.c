/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/src.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:21:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/src.h"

extern t_ret	ft_src_init_stream(t_src *self, t_istream *stream)
{
	FT_INIT(self, t_src);
	self->cur.col = self->cur.line = 1;
	self->in = stream;
	return (RET_OK);
}

inline t_ret	ft_src_init_file(t_src *self, char const *filename)
{
	FT_INIT(self, t_src);
	self->cur.col = self->cur.line = 1;
	return (ft_istream_open(&self->in_own, filename));
}

inline t_ret	ft_src_init_str(t_src *self, char const *str)
{
	FT_INIT(self, t_src);
	self->cur.col = self->cur.line = 1;
	return (ft_istream_mopen(&self->in_own, str));
}

inline t_ret	ft_src_init_nstr(t_src *self, char const *str, size_t n)
{
	FT_INIT(self, t_src);
	self->cur.col = self->cur.line = 1;
	return (ft_istream_mnopen(&self->in_own, str, n));
}

inline void		ft_src_dtor(t_src *self)
{
	if (!self->in)
		ft_istream_close(&self->in_own);
}
