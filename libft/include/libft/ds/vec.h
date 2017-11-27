/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/vec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 11:32:22 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_VEC_H
# define LIBFT_DS_VEC_H

# include "../mem.h"
# include "../str.h"
# include "../math.h"

# define FT_VEC_MIN_CAP 32

typedef struct	s_vi8
{
	int8_t		*buf;
	size_t		cap;
	size_t		len;
}				t_vi8;

typedef struct	s_vi16
{
	int16_t		*buf;
	size_t		cap;
	size_t		len;
}				t_vi16;

typedef struct	s_vi32
{
	int32_t		*buf;
	size_t		cap;
	size_t		len;
}				t_vi32;

typedef struct	s_vi64
{
	int64_t		*buf;
	size_t		cap;
	size_t		len;
}				t_vi64;

typedef struct	s_vu8
{
	uint8_t		*buf;
	size_t		cap;
	size_t		len;
}				t_vu8;

typedef struct	s_vu16
{
	uint16_t	*buf;
	size_t		cap;
	size_t		len;
}				t_vu16;

typedef struct	s_vu32
{
	uint32_t	*buf;
	size_t		cap;
	size_t		len;
}				t_vu32;

typedef struct	s_vu64
{
	uint64_t	*buf;
	size_t		cap;
	size_t		len;
}				t_vu64;

typedef struct	s_vstr
{
	char		**buf;
	size_t		cap;
	size_t		len;
}				t_vstr;

typedef struct	s_vec
{
	void		*buf;
	size_t		isz;
	size_t		cap;
	size_t		len;
}				t_vec;

typedef size_t	t_vsz;

extern void		ft_vi8_ctor(t_vi8 *s);
extern void		ft_vi8_dtor(t_vi8 *s, void(*idtor)(int8_t *i));
extern size_t	ft_vi8_size(t_vi8 *s);
extern int8_t	*ft_vi8_begin(t_vi8 *s);
extern int8_t	*ft_vi8_end(t_vi8 *s);
extern int8_t	*ft_vi8_at(t_vi8 *s, size_t i);
extern t_bool	ft_vi8_realloc(t_vi8 *s, size_t n);
extern t_bool	ft_vi8_grow(t_vi8 *s, size_t n);
extern t_bool	ft_vi8_ensure(t_vi8 *s, size_t n);
extern int8_t	*ft_vi8_pushn(t_vi8 *s, size_t n);
extern int8_t	*ft_vi8_pushnc(t_vi8 *s, int8_t const *b, size_t n);
extern int8_t	*ft_vi8_push(t_vi8 *s);
extern int8_t	*ft_vi8_pushc(t_vi8 *s, int8_t item);
extern int8_t	*ft_vi8_unshiftn(t_vi8 *s, size_t n);
extern int8_t	*ft_vi8_unshiftnc(t_vi8 *s, int8_t const *b, size_t n);
extern int8_t	*ft_vi8_unshift(t_vi8 *s);
extern int8_t	*ft_vi8_unshiftc(t_vi8 *s, int8_t item);
extern int8_t	*ft_vi8_putn(t_vi8 *s, size_t i, size_t n);
extern int8_t	*ft_vi8_putnc(t_vi8 *s, size_t i, int8_t const *b, size_t n);
extern int8_t	*ft_vi8_put(t_vi8 *s, size_t i);
extern int8_t	*ft_vi8_putc(t_vi8 *s, size_t i, int8_t item);
extern size_t	ft_vi8_popn(t_vi8 *s, size_t n, int8_t *out);
extern t_bool	ft_vi8_pop(t_vi8 *s, int8_t *out);
extern size_t	ft_vi8_shiftn(t_vi8 *s, size_t n, int8_t *out);
extern t_bool	ft_vi8_shift(t_vi8 *s, int8_t *out);
extern size_t	ft_vi8_removen(t_vi8 *s, size_t i, size_t n, int8_t *out);
extern t_bool	ft_vi8_remove(t_vi8 *s, size_t i, int8_t *out);

extern void		ft_vi16_ctor(t_vi16 *s);
extern void		ft_vi16_dtor(t_vi16 *s, void(*idtor)(int16_t *i));
extern size_t	ft_vi16_size(t_vi16 *s);
extern int16_t	*ft_vi16_begin(t_vi16 *s);
extern int16_t	*ft_vi16_end(t_vi16 *s);
extern int16_t	*ft_vi16_at(t_vi16 *s, size_t i);
extern t_bool	ft_vi16_realloc(t_vi16 *s, size_t n);
extern t_bool	ft_vi16_grow(t_vi16 *s, size_t n);
extern t_bool	ft_vi16_ensure(t_vi16 *s, size_t n);
extern int16_t	*ft_vi16_pushn(t_vi16 *s, size_t n);
extern int16_t	*ft_vi16_pushnc(t_vi16 *s, int16_t const *b, size_t n);
extern int16_t	*ft_vi16_push(t_vi16 *s);
extern int16_t	*ft_vi16_pushc(t_vi16 *s, int16_t item);
extern int16_t	*ft_vi16_unshiftn(t_vi16 *s, size_t n);
extern int16_t	*ft_vi16_unshiftnc(t_vi16 *s, int16_t const *b, size_t n);
extern int16_t	*ft_vi16_unshift(t_vi16 *s);
extern int16_t	*ft_vi16_unshiftc(t_vi16 *s, int16_t item);
extern int16_t	*ft_vi16_putn(t_vi16 *s, size_t i, size_t n);
extern int16_t	*ft_vi16_putnc(t_vi16 *s, size_t i, int16_t const *b, size_t n);
extern int16_t	*ft_vi16_put(t_vi16 *s, size_t i);
extern int16_t	*ft_vi16_putc(t_vi16 *s, size_t i, int16_t item);
extern size_t	ft_vi16_popn(t_vi16 *s, size_t n, int16_t *out);
extern t_bool	ft_vi16_pop(t_vi16 *s, int16_t *out);
extern size_t	ft_vi16_shiftn(t_vi16 *s, size_t n, int16_t *out);
extern t_bool	ft_vi16_shift(t_vi16 *s, int16_t *out);
extern size_t	ft_vi16_removen(t_vi16 *s, size_t i, size_t n, int16_t *out);
extern t_bool	ft_vi16_remove(t_vi16 *s, size_t i, int16_t *out);

extern void		ft_vi32_ctor(t_vi32 *s);
extern void		ft_vi32_dtor(t_vi32 *s, void(*idtor)(int32_t *i));
extern size_t	ft_vi32_size(t_vi32 *s);
extern int32_t	*ft_vi32_begin(t_vi32 *s);
extern int32_t	*ft_vi32_end(t_vi32 *s);
extern int32_t	*ft_vi32_at(t_vi32 *s, size_t i);
extern t_bool	ft_vi32_realloc(t_vi32 *s, size_t n);
extern t_bool	ft_vi32_grow(t_vi32 *s, size_t n);
extern t_bool	ft_vi32_ensure(t_vi32 *s, size_t n);
extern int32_t	*ft_vi32_pushn(t_vi32 *s, size_t n);
extern int32_t	*ft_vi32_pushnc(t_vi32 *s, int32_t const *b, size_t n);
extern int32_t	*ft_vi32_push(t_vi32 *s);
extern int32_t	*ft_vi32_pushc(t_vi32 *s, int32_t item);
extern int32_t	*ft_vi32_unshiftn(t_vi32 *s, size_t n);
extern int32_t	*ft_vi32_unshiftnc(t_vi32 *s, int32_t const *b, size_t n);
extern int32_t	*ft_vi32_unshift(t_vi32 *s);
extern int32_t	*ft_vi32_unshiftc(t_vi32 *s, int32_t item);
extern int32_t	*ft_vi32_putn(t_vi32 *s, size_t i, size_t n);
extern int32_t	*ft_vi32_putnc(t_vi32 *s, size_t i, int32_t const *b, size_t n);
extern int32_t	*ft_vi32_put(t_vi32 *s, size_t i);
extern int32_t	*ft_vi32_putc(t_vi32 *s, size_t i, int32_t item);
extern size_t	ft_vi32_popn(t_vi32 *s, size_t n, int32_t *out);
extern t_bool	ft_vi32_pop(t_vi32 *s, int32_t *out);
extern size_t	ft_vi32_shiftn(t_vi32 *s, size_t n, int32_t *out);
extern t_bool	ft_vi32_shift(t_vi32 *s, int32_t *out);
extern size_t	ft_vi32_removen(t_vi32 *s, size_t i, size_t n, int32_t *out);
extern t_bool	ft_vi32_remove(t_vi32 *s, size_t i, int32_t *out);

extern void		ft_vi64_ctor(t_vi64 *s);
extern void		ft_vi64_dtor(t_vi64 *s, void(*idtor)(int64_t *i));
extern size_t	ft_vi64_size(t_vi64 *s);
extern int64_t	*ft_vi64_begin(t_vi64 *s);
extern int64_t	*ft_vi64_end(t_vi64 *s);
extern int64_t	*ft_vi64_at(t_vi64 *s, size_t i);
extern t_bool	ft_vi64_realloc(t_vi64 *s, size_t n);
extern t_bool	ft_vi64_grow(t_vi64 *s, size_t n);
extern t_bool	ft_vi64_ensure(t_vi64 *s, size_t n);
extern int64_t	*ft_vi64_pushn(t_vi64 *s, size_t n);
extern int64_t	*ft_vi64_pushnc(t_vi64 *s, int64_t const *b, size_t n);
extern int64_t	*ft_vi64_push(t_vi64 *s);
extern int64_t	*ft_vi64_pushc(t_vi64 *s, int64_t item);
extern int64_t	*ft_vi64_unshiftn(t_vi64 *s, size_t n);
extern int64_t	*ft_vi64_unshiftnc(t_vi64 *s, int64_t const *b, size_t n);
extern int64_t	*ft_vi64_unshift(t_vi64 *s);
extern int64_t	*ft_vi64_unshiftc(t_vi64 *s, int64_t item);
extern int64_t	*ft_vi64_putn(t_vi64 *s, size_t i, size_t n);
extern int64_t	*ft_vi64_putnc(t_vi64 *s, size_t i, int64_t const *b, size_t n);
extern int64_t	*ft_vi64_put(t_vi64 *s, size_t i);
extern int64_t	*ft_vi64_putc(t_vi64 *s, size_t i, int64_t item);
extern size_t	ft_vi64_popn(t_vi64 *s, size_t n, int64_t *out);
extern t_bool	ft_vi64_pop(t_vi64 *s, int64_t *out);
extern size_t	ft_vi64_shiftn(t_vi64 *s, size_t n, int64_t *out);
extern t_bool	ft_vi64_shift(t_vi64 *s, int64_t *out);
extern size_t	ft_vi64_removen(t_vi64 *s, size_t i, size_t n, int64_t *out);
extern t_bool	ft_vi64_remove(t_vi64 *s, size_t i, int64_t *out);

extern void		ft_vstr_ctor(t_vstr *s);
extern void		ft_vstr_dtor(t_vstr *s, void(*idtor)(char **i));
extern size_t	ft_vstr_size(t_vstr *s);
extern char		**ft_vstr_begin(t_vstr *s);
extern char		**ft_vstr_end(t_vstr *s);
extern char		**ft_vstr_at(t_vstr *s, size_t i);
extern t_bool	ft_vstr_realloc(t_vstr *s, size_t n);
extern t_bool	ft_vstr_grow(t_vstr *s, size_t n);
extern t_bool	ft_vstr_ensure(t_vstr *s, size_t n);
extern char		**ft_vstr_pushn(t_vstr *s, size_t n);
extern char		**ft_vstr_pushnc(t_vstr *s, char const **b, size_t n);
extern char		**ft_vstr_push(t_vstr *s);
extern char		**ft_vstr_pushc(t_vstr *s, char *item);
extern char		**ft_vstr_unshiftn(t_vstr *s, size_t n);
extern char		**ft_vstr_unshiftnc(t_vstr *s, char const **b, size_t n);
extern char		**ft_vstr_unshift(t_vstr *s);
extern char		**ft_vstr_unshiftc(t_vstr *s, char *item);
extern char		**ft_vstr_putn(t_vstr *s, size_t i, size_t n);
extern char		**ft_vstr_putnc(t_vstr *s, size_t i, char const **b, size_t n);
extern char		**ft_vstr_put(t_vstr *s, size_t i);
extern char		**ft_vstr_putc(t_vstr *s, size_t i, char *item);
extern size_t	ft_vstr_popn(t_vstr *s, size_t n, char **out);
extern t_bool	ft_vstr_pop(t_vstr *s, char **out);
extern size_t	ft_vstr_shiftn(t_vstr *s, size_t n, char **out);
extern t_bool	ft_vstr_shift(t_vstr *s, char **out);
extern size_t	ft_vstr_removen(t_vstr *s, size_t i, size_t n, char **out);
extern t_bool	ft_vstr_remove(t_vstr *s, size_t i, char **out);

extern void		ft_vec_ctor(t_vec *s, size_t isz);
extern void		ft_vec_dtor(t_vec *s, void(*idtor)(void *i));
extern size_t	ft_vec_clean(t_vec *self, size_t n, t_dtor idtor);
extern size_t	ft_vec_size(t_vec *s);
extern void		*ft_vec_begin(t_vec *s);
extern void		*ft_vec_end(t_vec *s);
extern void		*ft_vec_at(t_vec *s, size_t i);
extern t_bool	ft_vec_realloc(t_vec *s, size_t n);
extern t_bool	ft_vec_grow(t_vec *s, size_t n);
extern t_bool	ft_vec_ensure(t_vec *s, size_t n);
extern void		*ft_vec_pushn(t_vec *s, size_t n);
extern void		*ft_vec_pushnc(t_vec *s, void const *b, size_t n);
extern void		*ft_vec_push(t_vec *s);
extern void		*ft_vec_pushc(t_vec *s, void *item);
extern void		*ft_vec_unshiftn(t_vec *s, size_t n);
extern void		*ft_vec_unshiftnc(t_vec *s, void const *b, size_t n);
extern void		*ft_vec_unshift(t_vec *s);
extern void		*ft_vec_unshiftc(t_vec *s, void *item);
extern void		*ft_vec_putn(t_vec *s, size_t i, size_t n);
extern void		*ft_vec_putnc(t_vec *s, size_t i, void const *b, size_t n);
extern void		*ft_vec_put(t_vec *s, size_t i);
extern void		*ft_vec_putc(t_vec *s, size_t i, void *item);
extern size_t	ft_vec_popn(t_vec *s, size_t n, void *out);
extern t_bool	ft_vec_pop(t_vec *s, void *out);
extern size_t	ft_vec_shiftn(t_vec *s, size_t n, void *out);
extern t_bool	ft_vec_shift(t_vec *s, void *out);
extern size_t	ft_vec_removen(t_vec *s, size_t i, size_t n, void *out);
extern t_bool	ft_vec_remove(t_vec *s, size_t i, void *out);

extern void		ft_vu8_ctor(t_vu8 *s);
extern void		ft_vu8_dtor(t_vu8 *s, void(*idtor)(uint8_t *));
extern size_t	ft_vu8_size(t_vu8 *s);
extern uint8_t	*ft_vu8_begin(t_vu8 *s);
extern uint8_t	*ft_vu8_end(t_vu8 *s);
extern uint8_t	*ft_vu8_at(t_vu8 *s, size_t i);
extern t_bool	ft_vu8_realloc(t_vu8 *s, size_t n);
extern t_bool	ft_vu8_grow(t_vu8 *s, size_t n);
extern t_bool	ft_vu8_ensure(t_vu8 *s, size_t n);
extern uint8_t	*ft_vu8_pushn(t_vu8 *s, size_t n);
extern uint8_t	*ft_vu8_pushnc(t_vu8 *s, uint8_t const *b, size_t n);
extern uint8_t	*ft_vu8_push(t_vu8 *s);
extern uint8_t	*ft_vu8_pushc(t_vu8 *s, uint8_t item);
extern uint8_t	*ft_vu8_unshiftn(t_vu8 *s, size_t n);
extern uint8_t	*ft_vu8_unshiftnc(t_vu8 *s, uint8_t const *b, size_t n);
extern uint8_t	*ft_vu8_unshift(t_vu8 *s);
extern uint8_t	*ft_vu8_unshiftc(t_vu8 *s, uint8_t item);
extern uint8_t	*ft_vu8_putn(t_vu8 *s, size_t i, size_t n);
extern uint8_t	*ft_vu8_putnc(t_vu8 *s, size_t i, uint8_t const *b, size_t n);
extern uint8_t	*ft_vu8_put(t_vu8 *s, size_t i);
extern uint8_t	*ft_vu8_putc(t_vu8 *s, size_t i, uint8_t item);
extern size_t	ft_vu8_popn(t_vu8 *s, size_t n, uint8_t *out);
extern t_bool	ft_vu8_pop(t_vu8 *s, uint8_t *out);
extern size_t	ft_vu8_shiftn(t_vu8 *s, size_t n, uint8_t *out);
extern t_bool	ft_vu8_shift(t_vu8 *s, uint8_t *out);
extern size_t	ft_vu8_removen(t_vu8 *s, size_t i, size_t n, uint8_t *out);
extern t_bool	ft_vu8_remove(t_vu8 *s, size_t i, uint8_t *out);

extern void		ft_vu16_ctor(t_vu16 *s);
extern void		ft_vu16_dtor(t_vu16 *s, void(*idtor)(uint16_t *));
extern size_t	ft_vu16_size(t_vu16 *s);
extern uint16_t	*ft_vu16_begin(t_vu16 *s);
extern uint16_t	*ft_vu16_end(t_vu16 *s);
extern uint16_t	*ft_vu16_at(t_vu16 *s, size_t i);
extern t_bool	ft_vu16_realloc(t_vu16 *s, size_t n);
extern t_bool	ft_vu16_grow(t_vu16 *s, size_t n);
extern t_bool	ft_vu16_ensure(t_vu16 *s, size_t n);
extern uint16_t	*ft_vu16_pushn(t_vu16 *s, size_t n);
extern uint16_t	*ft_vu16_pushnc(t_vu16 *s, uint16_t const *b, size_t n);
extern uint16_t	*ft_vu16_push(t_vu16 *s);
extern uint16_t	*ft_vu16_pushc(t_vu16 *s, uint16_t item);
extern uint16_t	*ft_vu16_unshiftn(t_vu16 *s, size_t n);
extern uint16_t	*ft_vu16_unshiftnc(t_vu16 *s, uint16_t const *b, size_t n);
extern uint16_t	*ft_vu16_unshift(t_vu16 *s);
extern uint16_t	*ft_vu16_unshiftc(t_vu16 *s, uint16_t item);
extern uint16_t	*ft_vu16_putn(t_vu16 *s, size_t i, size_t n);
extern uint16_t	*ft_vu16_putnc(t_vu16 *s, size_t i, uint16_t const *b, t_vsz n);
extern uint16_t	*ft_vu16_put(t_vu16 *s, size_t i);
extern uint16_t	*ft_vu16_putc(t_vu16 *s, size_t i, uint16_t item);
extern size_t	ft_vu16_popn(t_vu16 *s, size_t n, uint16_t *out);
extern t_bool	ft_vu16_pop(t_vu16 *s, uint16_t *out);
extern size_t	ft_vu16_shiftn(t_vu16 *s, size_t n, uint16_t *out);
extern t_bool	ft_vu16_shift(t_vu16 *s, uint16_t *out);
extern size_t	ft_vu16_removen(t_vu16 *s, size_t i, size_t n, uint16_t *out);
extern t_bool	ft_vu16_remove(t_vu16 *s, size_t i, uint16_t *out);

extern void		ft_vu32_ctor(t_vu32 *s);
extern void		ft_vu32_dtor(t_vu32 *s, void(*idtor)(uint32_t *));
extern size_t	ft_vu32_size(t_vu32 *s);
extern uint32_t	*ft_vu32_begin(t_vu32 *s);
extern uint32_t	*ft_vu32_end(t_vu32 *s);
extern uint32_t	*ft_vu32_at(t_vu32 *s, size_t i);
extern t_bool	ft_vu32_realloc(t_vu32 *s, size_t n);
extern t_bool	ft_vu32_grow(t_vu32 *s, size_t n);
extern t_bool	ft_vu32_ensure(t_vu32 *s, size_t n);
extern uint32_t	*ft_vu32_pushn(t_vu32 *s, size_t n);
extern uint32_t	*ft_vu32_pushnc(t_vu32 *s, uint32_t const *b, size_t n);
extern uint32_t	*ft_vu32_push(t_vu32 *s);
extern uint32_t	*ft_vu32_pushc(t_vu32 *s, uint32_t item);
extern uint32_t	*ft_vu32_unshiftn(t_vu32 *s, size_t n);
extern uint32_t	*ft_vu32_unshiftnc(t_vu32 *s, uint32_t const *b, size_t n);
extern uint32_t	*ft_vu32_unshift(t_vu32 *s);
extern uint32_t	*ft_vu32_unshiftc(t_vu32 *s, uint32_t item);
extern uint32_t	*ft_vu32_putn(t_vu32 *s, size_t i, size_t n);
extern uint32_t	*ft_vu32_putnc(t_vu32 *s, size_t i, uint32_t const *b, t_vsz n);
extern uint32_t	*ft_vu32_put(t_vu32 *s, size_t i);
extern uint32_t	*ft_vu32_putc(t_vu32 *s, size_t i, uint32_t item);
extern size_t	ft_vu32_popn(t_vu32 *s, size_t n, uint32_t *out);
extern t_bool	ft_vu32_pop(t_vu32 *s, uint32_t *out);
extern size_t	ft_vu32_shiftn(t_vu32 *s, size_t n, uint32_t *out);
extern t_bool	ft_vu32_shift(t_vu32 *s, uint32_t *out);
extern size_t	ft_vu32_removen(t_vu32 *s, size_t i, size_t n, uint32_t *out);
extern t_bool	ft_vu32_remove(t_vu32 *s, size_t i, uint32_t *out);

extern void		ft_vu64_ctor(t_vu64 *s);
extern void		ft_vu64_dtor(t_vu64 *s, void(*idtor)(uint64_t *));
extern size_t	ft_vu64_size(t_vu64 *s);
extern uint64_t	*ft_vu64_begin(t_vu64 *s);
extern uint64_t	*ft_vu64_end(t_vu64 *s);
extern uint64_t	*ft_vu64_at(t_vu64 *s, size_t i);
extern t_bool	ft_vu64_realloc(t_vu64 *s, size_t n);
extern t_bool	ft_vu64_grow(t_vu64 *s, size_t n);
extern t_bool	ft_vu64_ensure(t_vu64 *s, size_t n);
extern uint64_t	*ft_vu64_pushn(t_vu64 *s, size_t n);
extern uint64_t	*ft_vu64_pushnc(t_vu64 *s, uint64_t const *b, size_t n);
extern uint64_t	*ft_vu64_push(t_vu64 *s);
extern uint64_t	*ft_vu64_pushc(t_vu64 *s, uint64_t item);
extern uint64_t	*ft_vu64_unshiftn(t_vu64 *s, size_t n);
extern uint64_t	*ft_vu64_unshiftnc(t_vu64 *s, uint64_t const *b, size_t n);
extern uint64_t	*ft_vu64_unshift(t_vu64 *s);
extern uint64_t	*ft_vu64_unshiftc(t_vu64 *s, uint64_t item);
extern uint64_t	*ft_vu64_putn(t_vu64 *s, size_t i, size_t n);
extern uint64_t	*ft_vu64_putnc(t_vu64 *s, size_t i, uint64_t const *b, t_vsz n);
extern uint64_t	*ft_vu64_put(t_vu64 *s, size_t i);
extern uint64_t	*ft_vu64_putc(t_vu64 *s, size_t i, uint64_t item);
extern size_t	ft_vu64_popn(t_vu64 *s, size_t n, uint64_t *out);
extern t_bool	ft_vu64_pop(t_vu64 *s, uint64_t *out);
extern size_t	ft_vu64_shiftn(t_vu64 *s, size_t n, uint64_t *out);
extern t_bool	ft_vu64_shift(t_vu64 *s, uint64_t *out);
extern size_t	ft_vu64_removen(t_vu64 *s, size_t i, size_t n, uint64_t *out);
extern t_bool	ft_vu64_remove(t_vu64 *s, size_t i, uint64_t *out);

#endif
