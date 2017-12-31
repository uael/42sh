/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_src.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline t_src	*ft_lexer_src(t_lexer *self)
{
	t_src *src;

	if (ft_deq_size(&self->srcs) == 0 || !(src = ft_deq_at(&self->srcs, 0)))
		return (NULL);
	return (src);
}

inline void		ft_lexer_unshift(t_lexer *self, t_src *src)
{
	t_src	*s;

	s = ft_deq_unshiftc(&self->srcs, src);
	s->cur.src = s;
	self->src = s;
}
