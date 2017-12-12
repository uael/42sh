/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/tokv.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_TOKV_H
# define LIBFT_LEX_TOKV_H

# include "../ds.h"
# include "../io.h"

enum			e_tokv
{
	TOKV_STR,
	TOKV_IDENT,
	TOKV_I8,
	TOKV_I16,
	TOKV_I32,
	TOKV_I64,
	TOKV_U8,
	TOKV_U16,
	TOKV_U32,
	TOKV_U64,
	TOKV_F32,
	TOKV_F64
};

union			u_val
{
	t_dstr		str;
	t_dstr		ident;
	int8_t		i8;
	int16_t		i16;
	int32_t		i32;
	int64_t		i64;
	uint8_t		u8;
	uint16_t	u16;
	uint32_t	u32;
	uint64_t	u64;
	float		f32;
	double		f64;
};

typedef struct	s_tokv
{
	enum e_tokv	kind;
	union u_val	val;
}				t_tokv;

extern void		ft_tokv_init_str(t_tokv *self, char *str);
extern void		ft_tokv_init_ident(t_tokv *self, char *id);
extern void		ft_tokv_init_i8(t_tokv *self, int8_t i);
extern void		ft_tokv_init_i16(t_tokv *self, int16_t i);
extern void		ft_tokv_init_i32(t_tokv *self, int32_t i);
extern void		ft_tokv_init_i64(t_tokv *self, int64_t i);
extern void		ft_tokv_init_u8(t_tokv *self, uint8_t i);
extern void		ft_tokv_init_u16(t_tokv *self, uint16_t i);
extern void		ft_tokv_init_u32(t_tokv *self, uint32_t i);
extern void		ft_tokv_init_u64(t_tokv *self, uint64_t i);
extern void		ft_tokv_init_f32(t_tokv *self, float f);
extern void		ft_tokv_init_f64(t_tokv *self, double f);
extern void		ft_tokv_dtor(t_tokv *self);
extern t_dstr	*ft_tokv_str(t_tokv *self);
extern t_dstr	*ft_tokv_ident(t_tokv *self);

#endif
