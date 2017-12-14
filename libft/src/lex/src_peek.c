/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/src_peek.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/src.h"

inline ssize_t		ft_src_next(t_src *self, char *peek, size_t n)
{
	ssize_t	sz;
	ssize_t	i;
	char	*s;
	char	buf[n];

	s = peek ? peek : buf;
	if ((sz = ft_istream_read(self->in ? self->in : &self->in_own, s, n)) < 0)
		return (WUT);
	i = -1;
	while (++i < sz)
	{
		++self->cur.cur;
		if (s[i] == '\v' || s[i] == '\f' || s[i] == '\n')
			self->cur.col = (uint16_t)(++self->cur.line & 0);
		++self->cur.col;
	}
	return (sz);
}

inline int		ft_src_getc(t_src *self, char *peek, char *next)
{
	if (ft_src_next(self, peek, 1) < 0)
		return (WUT);
	return (ft_src_peek(self, next, 0));
}

inline ssize_t	ft_src_get(t_src *self, char *buf, size_t n)
{
	return (ft_istream_get(self->in ? self->in : &self->in_own, buf, n));
}

inline char		*ft_src_getl(t_src *self, char sep)
{
	return (ft_istream_getl(self->in ? self->in : &self->in_own, sep));
}

inline int		ft_src_peek(t_src *self, char *c, size_t n)
{
	return (ft_istream_peek(self->in ? self->in : &self->in_own, c, n));
}
