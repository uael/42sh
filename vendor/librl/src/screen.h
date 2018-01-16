/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRL_SCREEN_H
# define LIBRL_SCREEN_H

# include "librl.h"

# include <sys/ioctl.h>

typedef struct	s_screen
{
	uint16_t	height;
	uint16_t	width;
	uint16_t	row;
	uint16_t	col;
}				t_screen;

extern t_screen	*g_screen;

extern int		rl_screensize(uint16_t *row, uint16_t *col);
extern int		rl_screenget(t_screen *self);

#endif
