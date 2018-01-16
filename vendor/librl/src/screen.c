/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen.h"

static t_screen	g_stack_screen;
t_screen		*g_screen = &g_stack_screen;

int				rl_screensize(uint16_t *h, uint16_t *w)
{
	struct winsize	ws;

	if (ioctl(1, TIOCGWINSZ, &ws))
		return (THROW(WUT));
	if (h)
		*h = ws.ws_row;
	if (w)
		*w = ws.ws_col;
	return (YEP);
}

int				rl_screenget(t_screen *self)
{
	if (rl_screensize(&self->height, &self->width))
		return (WUT);
	return (YEP);
}
