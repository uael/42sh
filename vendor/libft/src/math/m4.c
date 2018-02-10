/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 12:18:13 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math/m4.h"

inline t_m1		ft_m1(float m0, float m1, float m2, float m3)
{
	return ((t_m1){{m0, m1, m2, m3}});
}

inline t_m4		ft_m4(t_m1 m0, t_m1 m1, t_m1 m2, t_m1 m3)
{
	return ((t_m4){
		.m[0][0] = m0.m[0], .m[1][0] = m0.m[1],
		.m[2][0] = m0.m[2], .m[3][0] = m0.m[3],
		.m[0][1] = m1.m[0], .m[1][1] = m1.m[1],
		.m[2][1] = m1.m[2], .m[3][1] = m1.m[3],
		.m[0][2] = m2.m[0], .m[1][2] = m2.m[1],
		.m[2][2] = m2.m[2], .m[3][2] = m2.m[3],
		.m[0][3] = m3.m[0], .m[1][3] = m3.m[1],
		.m[2][3] = m3.m[2], .m[3][3] = m3.m[3]});
}

inline t_m4		ft_m4_identity(void)
{
	return (ft_m4(
		ft_m1(1, 0, 0, 0),
		ft_m1(0, 1, 0, 0),
		ft_m1(0, 0, 1, 0),
		ft_m1(0, 0, 0, 1)));
}

inline t_m4		ft_m4_trans(t_v3 off)
{
	return (ft_m4(
		ft_m1(1, 0, 0, off.x),
		ft_m1(0, 1, 0, off.y),
		ft_m1(0, 0, 1, off.z),
		ft_m1(0, 0, 0, 1)));
}

inline t_m4		ft_m4_scale(t_v3 scale)
{
	return (ft_m4(
		ft_m1(scale.x, 0, 0, 0),
		ft_m1(0, scale.y, 0, 0),
		ft_m1(0, 0, scale.z, 0),
		ft_m1(0, 0, 0, 1)));
}
