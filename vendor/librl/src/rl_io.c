/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>

#include "rl.h"

int	rl_cursor(int ifd, int ofd)
{
	char	buf[32];
	uint	i;

	i = 0;
	if (write(ofd, "\x1b[6n", 4) != 4)
		return (THROW(WUT));
	while (++i < sizeof(buf))
		if (read(ifd, buf + i - 1, 1) != 1 || buf[i] == 'R')
			break;
	buf[i] = '\0';
	if (buf[0] != 27 || buf[1] != '[')
		return (THROW(WUT));
	return ((int)ft_atoi(ft_strchr(buf, ';') + 1));
}

int	rl_cols(int ifd, int ofd)
{
	struct winsize	ws;
	int				start;
	int				cols;
	char			seq[32];

	if (ioctl(1, TIOCGWINSZ, &ws) != -1 && ws.ws_col != 0)
		return (ws.ws_col);
	else
	{
		if ((start = rl_cursor(ifd, ofd)) == -1)
			return (WUT);
		if (write(ofd, "\x1b[999C", 6) != 6)
			return (THROW(WUT));
		if ((cols = rl_cursor(ifd, ofd)) == -1)
			return (WUT);
		if (cols > start)
		{
			ft_memcpy(seq, "\x1b[", sizeof("\x1b["));
			seq[ft_intstr(seq + sizeof("\x1b["), cols - start, 10)] = '\0';
			if (write(ofd, ft_strcat(seq, "D"), ft_strlen(seq)) < 0)
				return (THROW(WUT));
		}
		return (cols);
	}
}
