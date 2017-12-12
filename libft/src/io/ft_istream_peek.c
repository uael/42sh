/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istream_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 16:43:21 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/istream.h"

inline ssize_t	ft_istream_get(t_istream *self, char *buf, size_t n)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_get(&self->u.file, buf, n));
	if (self->kind == ISTREAM_MEM)
		return ((ssize_t)ft_imstream_get(&self->u.mem, buf, n));
	return (ENO_THROW(WUT, EBOUND));
}

inline int		ft_istream_peek(t_istream *self, char *c, size_t n)
{
	if (self->kind == ISTREAM_FILE)
		return (ft_ifstream_peek(&self->u.file, c, n));
	if (self->kind == ISTREAM_MEM)
		return (ft_imstream_peek(&self->u.mem, c, n) ? YEP : NOP);
	return (ENO_THROW(WUT, EBOUND));
}
