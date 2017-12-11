/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/mlx/win.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:40:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 08:23:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MLX_WIN_H
# define LIBFT_MLX_WIN_H

# include "img.h"

struct			s_xwin
{
	t_mlx		*mlx;
	void		*ptr;
};

extern t_xwin	*ft_xwin(t_mlx *mlx, int w, int h, char *n);
extern void		ft_xwin_dtor(t_xwin *self);
extern void		ft_xwin_clear(t_xwin *self);

#endif
