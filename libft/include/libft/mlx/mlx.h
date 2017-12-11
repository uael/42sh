/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/mlx/mlx.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:40:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 08:12:24 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MLX_MLX_H
# define LIBFT_MLX_MLX_H

# include "win.h"
# include "img.h"

# define MLX_ENMLX (-1)
# define MLX_ENWIN (-2)
# define MLX_ENIMG (-3)
# define MLX_EAIMG (-4)
# define MLX_EDRAW (-5)
# define MLX_ECWIN (-6)

struct			s_mlx
{
	void		*ptr;
	t_err_hdl	err_hdl;
	t_vec		wins;
	t_vec		imgs;
};

extern void		ft_mlx_ctor(t_mlx *self, t_err_hdl err_hdl);
extern void		ft_mlx_dtor(t_mlx *self);
extern void		ft_mlx_clear(t_mlx *self);

#endif
