/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:59:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:42:18 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mlx/mlx.h"

inline void		ft_mlx_ctor(t_mlx *self, t_err_hdl err_hdl)
{
	FT_INIT(self, t_mlx);
	self->err_hdl = err_hdl;
	if (!(self->ptr = mlx_init()))
		self->err_hdl(self, MLX_ENMLX);
	ft_vec_ctor(&self->wins, sizeof(t_xwin));
	ft_vec_ctor(&self->imgs, sizeof(t_ximg));
}

inline void		ft_mlx_dtor(t_mlx *self)
{
	ft_vec_dtor(&self->wins, (t_dtor)ft_xwin_dtor);
	ft_vec_dtor(&self->imgs, (t_dtor)ft_ximg_dtor);
	FT_INIT(self, t_xwin);
}

inline void		ft_mlx_clear(t_mlx *self)
{
	ft_vec_clear(&self->wins, (t_dtor)ft_xwin_dtor);
	ft_vec_clear(&self->imgs, (t_dtor)ft_ximg_dtor);
}
