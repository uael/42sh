/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/15 18:54:24 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_H
# define LIBFT_MATH_H

# include "tys.h"
# include "math/m4.h"
# include "math/v3.h"

# ifndef ABS
#  define ABS(a) ((a) < 0 ? -(a) : (a))
# endif

# ifndef MIN
#  define MIN(a, b) (((a)<(b))?(a):(b))
# endif

# ifndef MAX
#  define MAX(a, b) (((a)>(b))?(a):(b))
# endif

# ifndef ISPOW2
#  define ISPOW2(n) (((n) != 0) && (((n) & (~(n) + 1)) == (n)))
# endif

# define I8EQ(a, b) ((t_bool)((int8_t)(a) == (int8_t)(b)))
# define U8EQ(a, b) ((t_bool)((uint8_t)(a) == (uint8_t)(b)))
# define I16EQ(a, b) ((t_bool)((int16_t)(a) == (int16_t)(b)))
# define U16EQ(a, b) ((t_bool)((uint16_t)(a) == (uint16_t)(b)))
# define I32EQ(a, b) ((t_bool)((int32_t)(a) == (int32_t)(b)))
# define U32EQ(a, b) ((t_bool)((uint32_t)(a) == (uint32_t)(b)))
# define I64EQ(a, b) ((t_bool)((int64_t)(a) == (int64_t)(b)))
# define U64EQ(a, b) ((t_bool)((uint64_t)(a) == (uint64_t)(b)))
# define ISIZEEQ(a, b) ((t_bool)((ssize_t)(a) == (ssize_t)(b)))
# define USIZEEQ(a, b) ((t_bool)((size_t)(a) == (size_t)(b)))
# define F32EQ(a, b) ((t_bool)((float)(a) == (float)(b)))
# define F64EQ(a, b) ((t_bool)((double)(a) == (double)(b)))
# define STREQ(a, b) ((t_bool)(ft_strcmp(a, b) == 0))
# define ADDREQ(a, b) ((t_bool)(&(a) == &(b)))

# define I8CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define U8CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define I16CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define U16CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define I32CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define U32CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define I64CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define U64CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define ISIZECMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define USIZECMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define F32CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define F64CMP(a, b) ((int8_t)(((a) > (b)) - ((a) < (b))))
# define ADDRCMP(a, b) ((int8_t)((&(a) > &(b)) - (&(a) < &(b))))

typedef t_bool	(t_eqfn)(void *a, void *b);

extern int8_t	ft_i8max(int8_t a, int8_t b);
extern int16_t	ft_i16max(int16_t a, int16_t b);
extern int32_t	ft_i32max(int32_t a, int32_t b);
extern int64_t	ft_i64max(int64_t a, int64_t b);
extern ssize_t	ft_imax(ssize_t a, ssize_t b);

extern uint8_t	ft_u8max(uint8_t a, uint8_t b);
extern uint16_t	ft_u16max(uint16_t a, uint16_t b);
extern uint32_t	ft_u32max(uint32_t a, uint32_t b);
extern uint64_t	ft_u64max(uint64_t a, uint64_t b);
extern size_t	ft_umax(size_t a, size_t b);

extern int8_t	ft_i8min(int8_t a, int8_t b);
extern int16_t	ft_i16min(int16_t a, int16_t b);
extern int32_t	ft_i32min(int32_t a, int32_t b);
extern int64_t	ft_i64min(int64_t a, int64_t b);
extern ssize_t	ft_imin(ssize_t a, ssize_t b);

extern uint8_t	ft_u8min(uint8_t a, uint8_t b);
extern uint16_t	ft_u16min(uint16_t a, uint16_t b);
extern uint32_t	ft_u32min(uint32_t a, uint32_t b);
extern uint64_t	ft_u64min(uint64_t a, uint64_t b);
extern size_t	ft_umin(size_t a, size_t b);

extern uint64_t	ft_pow(int64_t n, int16_t p);
extern uint8_t	pow2_next8(uint8_t n);
extern uint16_t	pow2_next16(uint16_t n);
extern uint32_t	pow2_next32(uint32_t n);
extern uint64_t	pow2_next64(uint64_t n);
extern size_t	pow2_next(size_t n);

extern t_bool	ft_ieq(int a, int b);
extern t_bool	ft_ueq(unsigned int a, unsigned int b);
extern t_bool	ft_leq(long a, long b);
extern t_bool	ft_uleq(unsigned long a, unsigned long b);
extern t_bool	ft_lleq(long long int a, long long int b);
extern t_bool	ft_ulleq(unsigned long long int a, unsigned long long int b);
extern t_bool	ft_szeq(ssize_t a, ssize_t b);
extern t_bool	ft_uszeq(size_t a, size_t b);
extern t_bool	ft_streq(char const *a, char const *b);

#endif
