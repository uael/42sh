/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/src.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/src.h"

inline t_ret	ft_src_init_file(t_src *self, char const *filename)
{
	FT_INIT(self, t_src);
	self->cur.col = self->cur.line = 1;
	return (ft_istream_open(&self->in, filename));
}

inline t_ret	ft_src_init_str(t_src *self, char const *str)
{
	FT_INIT(self, t_src);
	self->cur.col = self->cur.line = 1;
	return (ft_istream_mopen(&self->in, str));
}

inline t_ret	ft_src_init_nstr(t_src *self, char const *str, size_t n)
{
	FT_INIT(self, t_src);
	self->cur.col = self->cur.line = 1;
	return (ft_istream_mnopen(&self->in, str, n));
}

inline void		ft_src_dtor(t_src *self)
{
	ft_istream_close(&self->in);
}
