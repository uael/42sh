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

#include "msh/screen.h"

static t_screen	g_stack_screen;
t_screen		*g_screen = &g_stack_screen;

int				sh_screenpos(int ifd, int ofd)
{
	char	buf[32];
	uint	i;

	i = 0;
	if (ft_write(ofd, "\x1b[6n", 4) != 4)
		return (THROW(WUT));
	while (++i < sizeof(buf))
		if (ft_read(ifd, buf + i - 1, 1) != 1 || buf[i] == 'R')
			break;
	buf[i] = '\0';
	if (buf[0] != 27 || buf[1] != '[')
		return (WUT);
	return ((int)ft_atoi(ft_strchr(buf, ';') + 1));
}

int				sh_screenwidth(int ifd, int ofd)
{
	struct winsize	ws;
	int				start;
	int				cols;
	char			seq[32];

	if (ioctl(1, TIOCGWINSZ, &ws) != -1 && ws.ws_col != 0)
		return (ws.ws_col);
	else
	{
		if ((start = sh_screenpos(ifd, ofd)) == -1)
			return (WUT);
		if (ft_write(ofd, "\x1b[999C", 6) != 6)
			return (THROW(WUT));
		if ((cols = sh_screenpos(ifd, ofd)) == -1)
			return (WUT);
		if (cols > start)
		{
			ft_memcpy(seq, "\x1b[", sizeof("\x1b["));
			seq[ft_intstr(seq + sizeof("\x1b["), cols - start, 10)] = '\0';
			if (ft_write(ofd, ft_strcat(seq, "D"), ft_strlen(seq)) < 0)
				return ((int16_t)THROW(WUT));
		}
		return (cols);
	}
}

int				sh_screenget(t_screen *self, int ifd, int ofd)
{
	int	width;

	if ((width = sh_screenwidth(ifd, ofd)) <= 0)
		return (WUT);
	self->width = (uint16_t)width;
	self->cursor = 0;
	return (YEP);
}
