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