/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_wli.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:59:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 18:03:03 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mlx/img.h"

inline void			ft_ximg_wli(t_ximg *self, t_v3 o, t_v3 t, int color)
{
	double	tab[6];
	int		state;

	tab[0] = fabs(o.x - t.x);
	tab[1] = o.x < t.x ? 1 : -1;
	tab[2] = fabs(o.y - t.y);
	tab[3] = o.y < t.y ? 1 : -1;
	tab[4] = (tab[0] > tab[2] ? tab[0] : -tab[2]) * 0.5;
	state = 1;
	while (state == 1 && !((int)o.x == (int)t.x && (int)o.y == (int)t.y))
	{
		ft_ximg_wdot(self, (int)o.x, (int)o.y, color);
		tab[5] = tab[4];
		state = 0;
		if (tab[5] > -tab[0] && (int)o.x != (int)t.x && (state = 1))
		{
			tab[4] -= tab[2];
			o.x += tab[1];
		}
		if (tab[5] < tab[2] && (int)o.y != (int)t.y && (state = 1))
		{
			tab[4] += tab[0];
			o.y += tab[3];
		}
	}
}
