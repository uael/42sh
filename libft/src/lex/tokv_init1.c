/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/tokv_init1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/tokv.h"

inline void	ft_tokv_init_u8(t_tokv *self, uint8_t i)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_U8;
	self->val.u8 = i;
}

inline void	ft_tokv_init_u16(t_tokv *self, uint16_t i)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_U16;
	self->val.u16 = i;
}

inline void	ft_tokv_init_u32(t_tokv *self, uint32_t i)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_U32;
	self->val.u32 = i;
}

inline void	ft_tokv_init_u64(t_tokv *self, uint64_t i)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_U64;
	self->val.u64 = i;
}

inline void	ft_tokv_init_f64(t_tokv *self, double f)
{
	FT_INIT(self, t_tokv);
	self->kind = TOKV_F64;
	self->val.f64 = f;
}
