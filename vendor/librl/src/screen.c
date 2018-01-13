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

int				rl_screenpos(uint16_t *row, uint16_t *col)
{
	char	buf[32];
	int		i;
	ssize_t	rd;

	i = -1;
	if (ft_write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
		return (THROW(WUT));
	rd = 0;
	while ((size_t)(++i + 1) < sizeof(buf))
		if ((rd = ft_read(STDIN_FILENO, buf + i, 1)) != 1 || buf[i] == 'R')
			break;
	if (rd < 0)
		return (WUT);
	buf[i + 1] = '\0';
	if (buf[0] != '\x1b' || buf[1] != '[' || buf[i] != 'R')
		return (WUT);
	if (row)
		*row = (uint16_t)ft_atoi(buf + 2);
	if (col)
		*col = (uint16_t)ft_atoi(ft_strchr(buf, ';') + 1);
	return (YEP);
}

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
	if (rl_screenpos(&self->row, &self->col))
		return (WUT);
	return (YEP);
}
