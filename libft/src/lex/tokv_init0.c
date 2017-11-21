/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/tokv_init0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/tokv.h"

inline void	ft_tokv_init_i8(t_tokv *self, int8_t i)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_I8;
	self->val.i8 = i;
}

inline void	ft_tokv_init_i16(t_tokv *self, int16_t i)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_I16;
	self->val.i16 = i;
}

inline void	ft_tokv_init_i32(t_tokv *self, int32_t i)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_I32;
	self->val.i32 = i;
}

inline void	ft_tokv_init_i64(t_tokv *self, int64_t i)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_I64;
	self->val.i64 = i;
}

inline void	ft_tokv_init_f32(t_tokv *self, float f)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_F32;
	self->val.f32 = f;
}
