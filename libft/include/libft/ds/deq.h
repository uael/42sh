/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/deq.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 08:13:57 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_DEQ_H
# define LIBFT_DS_DEQ_H

# include "../mem.h"
# include "../str.h"
# include "../math.h"

# define FT_DEQ_MIN_CAP 32

typedef struct	s_di8
{
	int8_t		*buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_di8;

typedef struct	s_di16
{
	int16_t		*buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_di16;

typedef struct	s_di32
{
	int32_t		*buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_di32;

typedef struct	s_di64
{
	int64_t		*buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_di64;

typedef struct	s_du8
{
	uint8_t		*buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_du8;

typedef struct	s_du16
{
	uint16_t	*buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_du16;

typedef struct	s_du32
{
	uint32_t	*buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_du32;

typedef struct	s_du64
{
	uint64_t	*buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_du64;

typedef struct	s_dqstr
{
	char		**buf;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_dqstr;

typedef struct	s_deq
{
	void		*buf;
	size_t		isz;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_deq;

typedef size_t	t_dsz;

extern void		ft_di8_ctor(t_di8 *s);
extern void		ft_di8_dtor(t_di8 *s, t_dtor idtor);
extern void		ft_di8_clear(t_di8 *s, t_dtor idtor);
extern size_t	ft_di8_clean(t_di8 *s, t_dtor idtor);
extern size_t	ft_di8_size(t_di8 *s);
extern int8_t	*ft_di8_begin(t_di8 *s);
extern int8_t	*ft_di8_end(t_di8 *s);
extern int8_t	*ft_di8_at(t_di8 *s, size_t i);
extern t_bool	ft_di8_realloc(t_di8 *s, size_t n);
extern t_bool	ft_di8_grow(t_di8 *s, size_t n);
extern t_bool	ft_di8_ensure(t_di8 *s, size_t n);
extern int8_t	*ft_di8_pushn(t_di8 *s, size_t n);
extern int8_t	*ft_di8_pushnc(t_di8 *s, int8_t const *b, size_t n);
extern int8_t	*ft_di8_push(t_di8 *s);
extern int8_t	*ft_di8_pushc(t_di8 *s, int8_t item);
extern int8_t	*ft_di8_unshiftn(t_di8 *s, size_t n);
extern int8_t	*ft_di8_unshiftnc(t_di8 *s, int8_t const *b, size_t n);
extern int8_t	*ft_di8_unshift(t_di8 *s);
extern int8_t	*ft_di8_unshiftc(t_di8 *s, int8_t item);
extern int8_t	*ft_di8_putn(t_di8 *s, size_t i, size_t n);
extern int8_t	*ft_di8_putnc(t_di8 *s, size_t i, int8_t const *b, size_t n);
extern int8_t	*ft_di8_put(t_di8 *s, size_t i);
extern int8_t	*ft_di8_putc(t_di8 *s, size_t i, int8_t item);
extern size_t	ft_di8_popn(t_di8 *s, size_t n, int8_t *out);
extern t_bool	ft_di8_pop(t_di8 *s, int8_t *out);
extern size_t	ft_di8_shiftn(t_di8 *s, size_t n, int8_t *out);
extern t_bool	ft_di8_shift(t_di8 *s, int8_t *out);
extern size_t	ft_di8_removen(t_di8 *s, size_t i, size_t n, int8_t *out);
extern t_bool	ft_di8_remove(t_di8 *s, size_t i, int8_t *out);

extern void		ft_di16_ctor(t_di16 *s);
extern void		ft_di16_dtor(t_di16 *s, t_dtor idtor);
extern void		ft_di16_clear(t_di16 *s, t_dtor idtor);
extern size_t	ft_di16_clean(t_di16 *s, t_dtor idtor);
extern size_t	ft_di16_size(t_di16 *s);
extern int16_t	*ft_di16_begin(t_di16 *s);
extern int16_t	*ft_di16_end(t_di16 *s);
extern int16_t	*ft_di16_at(t_di16 *s, size_t i);
extern t_bool	ft_di16_realloc(t_di16 *s, size_t n);
extern t_bool	ft_di16_grow(t_di16 *s, size_t n);
extern t_bool	ft_di16_ensure(t_di16 *s, size_t n);
extern int16_t	*ft_di16_pushn(t_di16 *s, size_t n);
extern int16_t	*ft_di16_pushnc(t_di16 *s, int16_t const *b, size_t n);
extern int16_t	*ft_di16_push(t_di16 *s);
extern int16_t	*ft_di16_pushc(t_di16 *s, int16_t item);
extern int16_t	*ft_di16_unshiftn(t_di16 *s, size_t n);
extern int16_t	*ft_di16_unshiftnc(t_di16 *s, int16_t const *b, size_t n);
extern int16_t	*ft_di16_unshift(t_di16 *s);
extern int16_t	*ft_di16_unshiftc(t_di16 *s, int16_t item);
extern int16_t	*ft_di16_putn(t_di16 *s, size_t i, size_t n);
extern int16_t	*ft_di16_putnc(t_di16 *s, size_t i, int16_t const *b, size_t n);
extern int16_t	*ft_di16_put(t_di16 *s, size_t i);
extern int16_t	*ft_di16_putc(t_di16 *s, size_t i, int16_t item);
extern size_t	ft_di16_popn(t_di16 *s, size_t n, int16_t *out);
extern t_bool	ft_di16_pop(t_di16 *s, int16_t *out);
extern size_t	ft_di16_shiftn(t_di16 *s, size_t n, int16_t *out);
extern t_bool	ft_di16_shift(t_di16 *s, int16_t *out);
extern size_t	ft_di16_removen(t_di16 *s, size_t i, size_t n, int16_t *out);
extern t_bool	ft_di16_remove(t_di16 *s, size_t i, int16_t *out);

extern void		ft_di32_ctor(t_di32 *s);
extern void		ft_di32_dtor(t_di32 *s, t_dtor idtor);
extern void		ft_di32_clear(t_di32 *s, t_dtor idtor);
extern size_t	ft_di32_clean(t_di32 *s, t_dtor idtor);
extern size_t	ft_di32_size(t_di32 *s);
extern int32_t	*ft_di32_begin(t_di32 *s);
extern int32_t	*ft_di32_end(t_di32 *s);
extern int32_t	*ft_di32_at(t_di32 *s, size_t i);
extern t_bool	ft_di32_realloc(t_di32 *s, size_t n);
extern t_bool	ft_di32_grow(t_di32 *s, size_t n);
extern t_bool	ft_di32_ensure(t_di32 *s, size_t n);
extern int32_t	*ft_di32_pushn(t_di32 *s, size_t n);
extern int32_t	*ft_di32_pushnc(t_di32 *s, int32_t const *b, size_t n);
extern int32_t	*ft_di32_push(t_di32 *s);
extern int32_t	*ft_di32_pushc(t_di32 *s, int32_t item);
extern int32_t	*ft_di32_unshiftn(t_di32 *s, size_t n);
extern int32_t	*ft_di32_unshiftnc(t_di32 *s, int32_t const *b, size_t n);
extern int32_t	*ft_di32_unshift(t_di32 *s);
extern int32_t	*ft_di32_unshiftc(t_di32 *s, int32_t item);
extern int32_t	*ft_di32_putn(t_di32 *s, size_t i, size_t n);
extern int32_t	*ft_di32_putnc(t_di32 *s, size_t i, int32_t const *b, size_t n);
extern int32_t	*ft_di32_put(t_di32 *s, size_t i);
extern int32_t	*ft_di32_putc(t_di32 *s, size_t i, int32_t item);
extern size_t	ft_di32_popn(t_di32 *s, size_t n, int32_t *out);
extern t_bool	ft_di32_pop(t_di32 *s, int32_t *out);
extern size_t	ft_di32_shiftn(t_di32 *s, size_t n, int32_t *out);
extern t_bool	ft_di32_shift(t_di32 *s, int32_t *out);
extern size_t	ft_di32_removen(t_di32 *s, size_t i, size_t n, int32_t *out);
extern t_bool	ft_di32_remove(t_di32 *s, size_t i, int32_t *out);

extern void		ft_di64_ctor(t_di64 *s);
extern void		ft_di64_dtor(t_di64 *s, t_dtor idtor);
extern void		ft_di64_clear(t_di64 *s, t_dtor idtor);
extern size_t	ft_di64_clean(t_di64 *s, t_dtor idtor);
extern size_t	ft_di64_size(t_di64 *s);
extern int64_t	*ft_di64_begin(t_di64 *s);
extern int64_t	*ft_di64_end(t_di64 *s);
extern int64_t	*ft_di64_at(t_di64 *s, size_t i);
extern t_bool	ft_di64_realloc(t_di64 *s, size_t n);
extern t_bool	ft_di64_grow(t_di64 *s, size_t n);
extern t_bool	ft_di64_ensure(t_di64 *s, size_t n);
extern int64_t	*ft_di64_pushn(t_di64 *s, size_t n);
extern int64_t	*ft_di64_pushnc(t_di64 *s, int64_t const *b, size_t n);
extern int64_t	*ft_di64_push(t_di64 *s);
extern int64_t	*ft_di64_pushc(t_di64 *s, int64_t item);
extern int64_t	*ft_di64_unshiftn(t_di64 *s, size_t n);
extern int64_t	*ft_di64_unshiftnc(t_di64 *s, int64_t const *b, size_t n);
extern int64_t	*ft_di64_unshift(t_di64 *s);
extern int64_t	*ft_di64_unshiftc(t_di64 *s, int64_t item);
extern int64_t	*ft_di64_putn(t_di64 *s, size_t i, size_t n);
extern int64_t	*ft_di64_putnc(t_di64 *s, size_t i, int64_t const *b, size_t n);
extern int64_t	*ft_di64_put(t_di64 *s, size_t i);
extern int64_t	*ft_di64_putc(t_di64 *s, size_t i, int64_t item);
extern size_t	ft_di64_popn(t_di64 *s, size_t n, int64_t *out);
extern t_bool	ft_di64_pop(t_di64 *s, int64_t *out);
extern size_t	ft_di64_shiftn(t_di64 *s, size_t n, int64_t *out);
extern t_bool	ft_di64_shift(t_di64 *s, int64_t *out);
extern size_t	ft_di64_removen(t_di64 *s, size_t i, size_t n, int64_t *out);
extern t_bool	ft_di64_remove(t_di64 *s, size_t i, int64_t *out);

extern void		ft_dqstr_ctor(t_dqstr *s);
extern void		ft_dqstr_dtor(t_dqstr *s, t_dtor idtor);
extern void		ft_dqstr_clear(t_dqstr *s, t_dtor idtor);
extern size_t	ft_dqstr_clean(t_dqstr *s, t_dtor idtor);
extern size_t	ft_dqstr_size(t_dqstr *s);
extern char		**ft_dqstr_begin(t_dqstr *s);
extern char		**ft_dqstr_end(t_dqstr *s);
extern char		**ft_dqstr_at(t_dqstr *s, size_t i);
extern t_bool	ft_dqstr_realloc(t_dqstr *s, size_t n);
extern t_bool	ft_dqstr_grow(t_dqstr *s, size_t n);
extern t_bool	ft_dqstr_ensure(t_dqstr *s, size_t n);
extern char		**ft_dqstr_pushn(t_dqstr *s, size_t n);
extern char		**ft_dqstr_pushnc(t_dqstr *s, char const **b, size_t n);
extern char		**ft_dqstr_push(t_dqstr *s);
extern char		**ft_dqstr_pushc(t_dqstr *s, char *item);
extern char		**ft_dqstr_unshiftn(t_dqstr *s, size_t n);
extern char		**ft_dqstr_unshiftnc(t_dqstr *s, char const **b, size_t n);
extern char		**ft_dqstr_unshift(t_dqstr *s);
extern char		**ft_dqstr_unshiftc(t_dqstr *s, char *item);
extern char		**ft_dqstr_putn(t_dqstr *s, size_t i, size_t n);
extern char		**ft_dqstr_putnc(t_dqstr *s, t_dsz i, char const **b, size_t n);
extern char		**ft_dqstr_put(t_dqstr *s, size_t i);
extern char		**ft_dqstr_putc(t_dqstr *s, size_t i, char *item);
extern size_t	ft_dqstr_popn(t_dqstr *s, size_t n, char **out);
extern t_bool	ft_dqstr_pop(t_dqstr *s, char **out);
extern size_t	ft_dqstr_shiftn(t_dqstr *s, size_t n, char **out);
extern t_bool	ft_dqstr_shift(t_dqstr *s, char **out);
extern size_t	ft_dqstr_removen(t_dqstr *s, size_t i, size_t n, char **out);
extern t_bool	ft_dqstr_remove(t_dqstr *s, size_t i, char **out);

extern void		ft_deq_ctor(t_deq *s, size_t isz);
extern void		ft_deq_dtor(t_deq *s, t_dtor idtor);
extern void		ft_deq_clear(t_deq *s, t_dtor idtor);
extern size_t	ft_deq_clean(t_deq *s, t_dtor idtor);
extern size_t	ft_deq_size(t_deq *s);
extern void		*ft_deq_begin(t_deq *s);
extern void		*ft_deq_end(t_deq *s);
extern void		*ft_deq_at(t_deq *s, size_t i);
extern t_bool	ft_deq_realloc(t_deq *s, size_t n);
extern t_bool	ft_deq_grow(t_deq *s, size_t n);
extern t_bool	ft_deq_ensure(t_deq *s, size_t n);
extern void		*ft_deq_pushn(t_deq *s, size_t n);
extern void		*ft_deq_pushnc(t_deq *s, void const *b, size_t n);
extern void		*ft_deq_push(t_deq *s);
extern void		*ft_deq_pushc(t_deq *s, void *item);
extern void		*ft_deq_unshiftn(t_deq *s, size_t n);
extern void		*ft_deq_unshiftnc(t_deq *s, void const *b, size_t n);
extern void		*ft_deq_unshift(t_deq *s);
extern void		*ft_deq_unshiftc(t_deq *s, void *item);
extern void		*ft_deq_putn(t_deq *s, size_t i, size_t n);
extern void		*ft_deq_putnc(t_deq *s, size_t i, void const *b, size_t n);
extern void		*ft_deq_put(t_deq *s, size_t i);
extern void		*ft_deq_putc(t_deq *s, size_t i, void *item);
extern size_t	ft_deq_popn(t_deq *s, size_t n, void *out);
extern t_bool	ft_deq_pop(t_deq *s, void *out);
extern size_t	ft_deq_shiftn(t_deq *s, size_t n, void *out);
extern t_bool	ft_deq_shift(t_deq *s, void *out);
extern size_t	ft_deq_removen(t_deq *s, size_t i, size_t n, void *out);
extern t_bool	ft_deq_remove(t_deq *s, size_t i, void *out);

extern void		ft_du8_ctor(t_du8 *s);
extern void		ft_du8_dtor(t_du8 *s, t_dtor idtor);
extern void		ft_du8_clear(t_du8 *s, t_dtor idtor);
extern size_t	ft_du8_clean(t_du8 *s, t_dtor idtor);
extern size_t	ft_du8_size(t_du8 *s);
extern uint8_t	*ft_du8_begin(t_du8 *s);
extern uint8_t	*ft_du8_end(t_du8 *s);
extern uint8_t	*ft_du8_at(t_du8 *s, size_t i);
extern t_bool	ft_du8_realloc(t_du8 *s, size_t n);
extern t_bool	ft_du8_grow(t_du8 *s, size_t n);
extern t_bool	ft_du8_ensure(t_du8 *s, size_t n);
extern uint8_t	*ft_du8_pushn(t_du8 *s, size_t n);
extern uint8_t	*ft_du8_pushnc(t_du8 *s, uint8_t const *b, size_t n);
extern uint8_t	*ft_du8_push(t_du8 *s);
extern uint8_t	*ft_du8_pushc(t_du8 *s, uint8_t item);
extern uint8_t	*ft_du8_unshiftn(t_du8 *s, size_t n);
extern uint8_t	*ft_du8_unshiftnc(t_du8 *s, uint8_t const *b, size_t n);
extern uint8_t	*ft_du8_unshift(t_du8 *s);
extern uint8_t	*ft_du8_unshiftc(t_du8 *s, uint8_t item);
extern uint8_t	*ft_du8_putn(t_du8 *s, size_t i, size_t n);
extern uint8_t	*ft_du8_putnc(t_du8 *s, size_t i, uint8_t const *b, size_t n);
extern uint8_t	*ft_du8_put(t_du8 *s, size_t i);
extern uint8_t	*ft_du8_putc(t_du8 *s, size_t i, uint8_t item);
extern size_t	ft_du8_popn(t_du8 *s, size_t n, uint8_t *out);
extern t_bool	ft_du8_pop(t_du8 *s, uint8_t *out);
extern size_t	ft_du8_shiftn(t_du8 *s, size_t n, uint8_t *out);
extern t_bool	ft_du8_shift(t_du8 *s, uint8_t *out);
extern size_t	ft_du8_removen(t_du8 *s, size_t i, size_t n, uint8_t *out);
extern t_bool	ft_du8_remove(t_du8 *s, size_t i, uint8_t *out);

extern void		ft_du16_ctor(t_du16 *s);
extern void		ft_du16_dtor(t_du16 *s, t_dtor idtor);
extern void		ft_du16_clear(t_du16 *s, t_dtor idtor);
extern size_t	ft_du16_clean(t_du16 *s, t_dtor idtor);
extern size_t	ft_du16_size(t_du16 *s);
extern uint16_t	*ft_du16_begin(t_du16 *s);
extern uint16_t	*ft_du16_end(t_du16 *s);
extern uint16_t	*ft_du16_at(t_du16 *s, size_t i);
extern t_bool	ft_du16_realloc(t_du16 *s, size_t n);
extern t_bool	ft_du16_grow(t_du16 *s, size_t n);
extern t_bool	ft_du16_ensure(t_du16 *s, size_t n);
extern uint16_t	*ft_du16_pushn(t_du16 *s, size_t n);
extern uint16_t	*ft_du16_pushnc(t_du16 *s, uint16_t const *b, size_t n);
extern uint16_t	*ft_du16_push(t_du16 *s);
extern uint16_t	*ft_du16_pushc(t_du16 *s, uint16_t item);
extern uint16_t	*ft_du16_unshiftn(t_du16 *s, size_t n);
extern uint16_t	*ft_du16_unshiftnc(t_du16 *s, uint16_t const *b, size_t n);
extern uint16_t	*ft_du16_unshift(t_du16 *s);
extern uint16_t	*ft_du16_unshiftc(t_du16 *s, uint16_t item);
extern uint16_t	*ft_du16_putn(t_du16 *s, size_t i, size_t n);
extern uint16_t	*ft_du16_putnc(t_du16 *s, size_t i, uint16_t const *b, t_dsz n);
extern uint16_t	*ft_du16_put(t_du16 *s, size_t i);
extern uint16_t	*ft_du16_putc(t_du16 *s, size_t i, uint16_t item);
extern size_t	ft_du16_popn(t_du16 *s, size_t n, uint16_t *out);
extern t_bool	ft_du16_pop(t_du16 *s, uint16_t *out);
extern size_t	ft_du16_shiftn(t_du16 *s, size_t n, uint16_t *out);
extern t_bool	ft_du16_shift(t_du16 *s, uint16_t *out);
extern size_t	ft_du16_removen(t_du16 *s, size_t i, size_t n, uint16_t *out);
extern t_bool	ft_du16_remove(t_du16 *s, size_t i, uint16_t *out);

extern void		ft_du32_ctor(t_du32 *s);
extern void		ft_du32_dtor(t_du32 *s, t_dtor idtor);
extern void		ft_du32_clear(t_du32 *s, t_dtor idtor);
extern size_t	ft_du32_clean(t_du32 *s, t_dtor idtor);
extern size_t	ft_du32_size(t_du32 *s);
extern uint32_t	*ft_du32_begin(t_du32 *s);
extern uint32_t	*ft_du32_end(t_du32 *s);
extern uint32_t	*ft_du32_at(t_du32 *s, size_t i);
extern t_bool	ft_du32_realloc(t_du32 *s, size_t n);
extern t_bool	ft_du32_grow(t_du32 *s, size_t n);
extern t_bool	ft_du32_ensure(t_du32 *s, size_t n);
extern uint32_t	*ft_du32_pushn(t_du32 *s, size_t n);
extern uint32_t	*ft_du32_pushnc(t_du32 *s, uint32_t const *b, size_t n);
extern uint32_t	*ft_du32_push(t_du32 *s);
extern uint32_t	*ft_du32_pushc(t_du32 *s, uint32_t item);
extern uint32_t	*ft_du32_unshiftn(t_du32 *s, size_t n);
extern uint32_t	*ft_du32_unshiftnc(t_du32 *s, uint32_t const *b, size_t n);
extern uint32_t	*ft_du32_unshift(t_du32 *s);
extern uint32_t	*ft_du32_unshiftc(t_du32 *s, uint32_t item);
extern uint32_t	*ft_du32_putn(t_du32 *s, size_t i, size_t n);
extern uint32_t	*ft_du32_putnc(t_du32 *s, size_t i, uint32_t const *b, t_dsz n);
extern uint32_t	*ft_du32_put(t_du32 *s, size_t i);
extern uint32_t	*ft_du32_putc(t_du32 *s, size_t i, uint32_t item);
extern size_t	ft_du32_popn(t_du32 *s, size_t n, uint32_t *out);
extern t_bool	ft_du32_pop(t_du32 *s, uint32_t *out);
extern size_t	ft_du32_shiftn(t_du32 *s, size_t n, uint32_t *out);
extern t_bool	ft_du32_shift(t_du32 *s, uint32_t *out);
extern size_t	ft_du32_removen(t_du32 *s, size_t i, size_t n, uint32_t *out);
extern t_bool	ft_du32_remove(t_du32 *s, size_t i, uint32_t *out);

extern void		ft_du64_ctor(t_du64 *s);
extern void		ft_du64_dtor(t_du64 *s, t_dtor idtor);
extern void		ft_du64_clear(t_du64 *s, t_dtor idtor);
extern size_t	ft_du64_clean(t_du64 *s, t_dtor idtor);
extern size_t	ft_du64_size(t_du64 *s);
extern uint64_t	*ft_du64_begin(t_du64 *s);
extern uint64_t	*ft_du64_end(t_du64 *s);
extern uint64_t	*ft_du64_at(t_du64 *s, size_t i);
extern t_bool	ft_du64_realloc(t_du64 *s, size_t n);
extern t_bool	ft_du64_grow(t_du64 *s, size_t n);
extern t_bool	ft_du64_ensure(t_du64 *s, size_t n);
extern uint64_t	*ft_du64_pushn(t_du64 *s, size_t n);
extern uint64_t	*ft_du64_pushnc(t_du64 *s, uint64_t const *b, size_t n);
extern uint64_t	*ft_du64_push(t_du64 *s);
extern uint64_t	*ft_du64_pushc(t_du64 *s, uint64_t item);
extern uint64_t	*ft_du64_unshiftn(t_du64 *s, size_t n);
extern uint64_t	*ft_du64_unshiftnc(t_du64 *s, uint64_t const *b, size_t n);
extern uint64_t	*ft_du64_unshift(t_du64 *s);
extern uint64_t	*ft_du64_unshiftc(t_du64 *s, uint64_t item);
extern uint64_t	*ft_du64_putn(t_du64 *s, size_t i, size_t n);
extern uint64_t	*ft_du64_putnc(t_du64 *s, size_t i, uint64_t const *b, t_dsz n);
extern uint64_t	*ft_du64_put(t_du64 *s, size_t i);
extern uint64_t	*ft_du64_putc(t_du64 *s, size_t i, uint64_t item);
extern size_t	ft_du64_popn(t_du64 *s, size_t n, uint64_t *out);
extern t_bool	ft_du64_pop(t_du64 *s, uint64_t *out);
extern size_t	ft_du64_shiftn(t_du64 *s, size_t n, uint64_t *out);
extern t_bool	ft_du64_shift(t_du64 *s, uint64_t *out);
extern size_t	ft_du64_removen(t_du64 *s, size_t i, size_t n, uint64_t *out);
extern t_bool	ft_du64_remove(t_du64 *s, size_t i, uint64_t *out);

#endif
