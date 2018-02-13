/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/math/m4.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 10:28:45 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 11:58:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_M4_H
# define LIBFT_MATH_M4_H

# include "v3.h"

typedef struct	s_m1_fields
{
	float		m0;
	float		m1;
	float		m2;
	float		m3;
}				t_m1_fields;

typedef union	u_m1
{
	t_m1_fields	f;
	float		m[4];
}				t_m1;

typedef struct	s_m4_fields
{
	t_m1		m0;
	t_m1		m1;
	t_m1		m2;
	t_m1		m3;
}				t_m4_fields;

typedef union	u_m4
{
	t_m4_fields	f;
	float		m[4][4];
}				t_m4;

extern t_m1		ft_m1(float m0, float m1, float m2, float m3);
extern t_m4		ft_m4(t_m1 m0, t_m1 m1, t_m1 m2, t_m1 m3);
extern t_m4		ft_m4_identity(void);
extern t_m4		ft_m4_transx(float s);
extern t_m4		ft_m4_transy(float s);
extern t_m4		ft_m4_transz(float s);
extern t_m4		ft_m4_trans(t_v3 off);
extern t_m4		ft_m4_scale(t_v3 scale);
extern t_m4		ft_m4_rotx(float rad);
extern t_m4		ft_m4_roty(float rad);
extern t_m4		ft_m4_rotz(float rad);
extern t_m4		ft_m4_rot(float rad, t_v3 axis);
extern t_m4		ft_m4_mul(t_m4 a, t_m4 b);
extern t_v3		ft_m4_apply(t_m4 m, t_v3 to);

#endif
