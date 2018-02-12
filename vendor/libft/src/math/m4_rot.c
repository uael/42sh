/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m4_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 21:32:14 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math/m4.h"

inline t_m4		ft_m4_rotx(float rad)
{
	float s;
	float c;

	s = sinf(rad);
	c = cosf(rad);
	return (ft_m4(
		ft_m1(1, 0, 0, 0),
		ft_m1(0, c, -s, 0),
		ft_m1(0, s, c, 0),
		ft_m1(0, 0, 0, 1)));
}

inline t_m4		ft_m4_roty(float rad)
{
	float s;
	float c;

	s = sinf(rad);
	c = cosf(rad);
	return (ft_m4(
		ft_m1(c, 0, s, 0),
		ft_m1(0, 1, 0, 0),
		ft_m1(-s, 0, c, 0),
		ft_m1(0, 0, 0, 1)));
}

inline t_m4		ft_m4_rotz(float rad)
{
	float s;
	float c;

	s = sinf(rad);
	c = cosf(rad);
	return (ft_m4(
		ft_m1(c, -s, 0, 0),
		ft_m1(s, c, 0, 0),
		ft_m1(0, 0, 1, 0),
		ft_m1(0, 0, 0, 1)));
}

inline t_m4		ft_m4_rot(float rad, t_v3 axis)
{
	t_v3	n;
	float	s;
	float	c;

	n = ft_v3_nor(axis);
	s = sinf(rad);
	c = cosf(rad);
	return (ft_m4(
		ft_m1(c + n.x * n.x * (1 - c), n.x * n.y * (1 - c) - n.z * s,
			n.x * n.z * (1 - c) + n.y * s, 0),
		ft_m1(n.y * n.x * (1 - c) + n.z * s, c + n.y * n.y * (1 - c),
			n.y * n.z * (1 - c) - n.x * s, 0),
		ft_m1(n.z * n.x * (1 - c) - n.y * s, n.z * n.y * (1 - c) + n.x * s,
			c + n.z * n.z * (1 - c), 0),
		ft_m1(0, 0, 0, 1)));
}

inline t_v3		ft_m4_apply(t_m4 m, t_v3 to)
{
	t_v3	v;
	float	w;

	v = ft_v3(
		to.x * m.m[0][0] + to.y * m.m[1][0] + to.z * m.m[2][0] + m.m[3][0],
		to.x * m.m[0][1] + to.y * m.m[1][1] + to.z * m.m[2][1] + m.m[3][1],
		to.x * m.m[0][2] + to.y * m.m[1][2] + to.z * m.m[2][2] + m.m[3][2]);
	w = m.m[0][3] * to.x + m.m[1][3] * to.y + m.m[2][3] * to.z + m.m[3][3];
	if (w != 0 && w != 1)
		return (ft_v3(v.x / w, v.y / w, v.z / w));
	return (v);
}
