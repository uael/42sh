/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m4_mul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 11:55:17 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math/m4.h"
#include "libft/lib.h"
#include "libft/str.h"

inline t_m4		ft_m4_mul(t_m4 a, t_m4 b)
{
	t_m4	m;
	int		i;
	int		j;
	int		k;
	float	sum;

	ft_bzero(&m, sizeof(t_m4));
	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4 && (k = -1))
		{
			sum = 0;
			while (++k < 4)
				sum += a.m[k][j] * b.m[i][k];
			m.m[i][j] = sum;
		}
	return (m);
}
