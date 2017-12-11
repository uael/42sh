/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/math/v3.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 10:28:45 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:34:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_V3_H
# define LIBFT_MATH_V3_H

# include <math.h>

typedef struct	s_v3
{
	float		x;
	float		y;
	float		z;
}				t_v3;

extern t_v3		ft_v3(float x, float y, float z);
extern t_v3		ft_v3_add(t_v3 a, t_v3 b);
extern t_v3		ft_v3_sub(t_v3 a, t_v3 b);
extern t_v3		ft_v3_mul(t_v3 a, t_v3 b);
extern t_v3		ft_v3_div(t_v3 a, t_v3 b);
extern float	ft_v3_dot(t_v3 a, t_v3 b);
extern float	ft_v3_ang(t_v3 a, t_v3 b);
extern float	ft_v3_len(t_v3 a);
extern t_v3		ft_v3_nor(t_v3 a);

#endif
