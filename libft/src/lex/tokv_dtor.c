/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/tokv_dtor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/tokv.h"

inline void	ft_tokv_dtor(t_tokv *self)
{
	if (self->kind == TOKV_IDENT)
		ft_dstr_dtor(&self->val.ident, NULL);
	if (self->kind == TOKV_STR)
		ft_dstr_dtor(&self->val.str, NULL);
}

inline t_dstr	*ft_tokv_str(t_tokv *self)
{
	return (&self->val.str);
}

inline t_dstr	*ft_tokv_ident(t_tokv *self)
{
	return (&self->val.ident);
}
