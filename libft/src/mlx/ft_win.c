/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_win.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:59:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:18:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mlx/win.h"
#include "libft/mlx/mlx.h"

extern t_xwin	*ft_xwin(t_mlx *mlx, int w, int h, char *n)
{
	t_xwin *win;

	if (!(win = ft_vec_push(&mlx->wins)))
	{
		mlx->err_hdl(mlx, errno);
		return (NULL);
	}
	FT_INIT(win, t_xwin);
	if (!(win->ptr = mlx_new_window(mlx->ptr, w, h, n)))
	{
		mlx->err_hdl(mlx, MLX_ENWIN);
		return (NULL);
	}
	win->mlx = mlx;
	return (win);
}

extern void		ft_xwin_dtor(t_xwin *self)
{
	mlx_destroy_window(self->mlx->ptr, self->ptr);
	FT_INIT(self, t_xwin);
}

extern void		ft_xwin_clear(t_xwin *self)
{
	if (!mlx_clear_window(self->mlx->ptr, self->ptr))
		self->mlx->err_hdl(self, MLX_ECWIN);
}
