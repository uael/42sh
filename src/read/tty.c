/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read/tty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/read.h"

static void	rd_redirect(void) {
	TTY	t;
	int	fd;

	fd = open("/dev/null", O_WRONLY);
	if (tcgetattr(STDIN_FILENO, &t) == -1 && errno == EIO)
		dup2(fd, STDIN_FILENO);
	if (tcgetattr(STDOUT_FILENO, &t) == -1 && errno == EIO)
		dup2(fd, STDOUT_FILENO);
	if (tcgetattr(STDERR_FILENO, &t) == -1 && errno == EIO)
		dup2(fd, STDERR_FILENO);
	close(fd);
}

inline int	sh_rawmode(int fd)
{
	int st;

	if (g_mode == RL_NONE)
	{
		if ((st = tcgetattr(fd, &g_orig_mode)) == -1 && errno == EIO)
			rd_redirect();
		else if (st == -1)
			return (WUT);
		g_raw_mode = g_orig_mode;
		g_raw_mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | OPOST);
		g_raw_mode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		g_raw_mode.c_cflag |= (CS8);
		g_raw_mode.c_cc[VMIN] = 1;
		g_raw_mode.c_cc[VTIME] = 0;
		g_mode = RL_OFF;
	}
	if (g_mode != RL_INSERT)
	{
		if ((st = tcsetattr(fd, TCSADRAIN, &g_raw_mode)) == -1 && errno == EIO)
			rd_redirect();
		else if (st == -1)
			return (WUT);
		g_mode = RL_INSERT;
	}
	return (YEP);
}

inline int	sh_offmode(int fd)
{
	int st;

	if (g_mode != RL_OFF)
	{
		if ((st = tcsetattr(fd, TCSADRAIN, &g_orig_mode)) == -1 && errno == EIO)
			rd_redirect();
		else if (st == -1)
			return (YEP);
		g_mode = RL_OFF;
	}
	return (YEP);
}

int			sh_screenpos(int ifd, int ofd)
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

int			sh_screenwidth(int ifd, int ofd)
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
