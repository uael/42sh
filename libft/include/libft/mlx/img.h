/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/mlx/img.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:40:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 21:15:38 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MLX_IMG_H
# define LIBFT_MLX_IMG_H

# include <mlx.h>

# include "../lib.h"
# include "../ds.h"
# include "../io.h"
# include "../fs.h"
# include "../math.h"

typedef struct s_mlx	t_mlx;
typedef struct s_xwin	t_xwin;

typedef struct			s_ximg
{
	t_mlx				*mlx;
	void				*ptr;
	int					width;
	int					height;
	char				*li;
	int					bpp;
	int					lisz;
	int					endian;
}						t_ximg;

extern t_ximg			*ft_ximg(t_mlx *mlx, int width, int height);
extern void				ft_ximg_dtor(t_ximg *self);
extern void				ft_ximg_clear(t_ximg *self);
extern void				ft_ximg_draw(t_ximg *self, t_xwin *win, int x, int y);
extern void				ft_ximg_wdot(t_ximg *self, int x, int y, int color);
extern void				ft_ximg_wli(t_ximg *self, t_v3 o, t_v3 t, int color);

#endif
