/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/tokv_init2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/tokv.h"

inline t_st	ft_tokv_init_str(t_tokv *self, char *str)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_STR;
	ft_dstr_ctor(&self->val.str);
	return (ft_dstr_append(&self->val.str, str) ? OK : ENO);
}

inline t_st	ft_tokv_init_ident(t_tokv *self, char *id)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_IDENT;
	ft_dstr_ctor(&self->val.ident);
	return (ft_dstr_append(&self->val.ident, id)  ? OK : ENO);
}
