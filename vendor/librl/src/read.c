/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>

#include "read.h"

t_rmode			g_mode = RL_NONE;
TTY				g_orig_mode;
TTY				g_raw_mode;

static t_bool	g_screen_init = 0;

void			rd_sigwinch(int signo)
{
	(void)signo;
	rl_screenget(g_screen);
}

void			rl_finalize(int fd)
{
	if (isatty(fd))
		return (rl_ttyfinalize(fd));
	rl_nottyfinalize(fd);
}

void			rl_dtor(void)
{
	rl_ttydtor();
	rl_nottydtor();
}

int				rl_getline(int fd, char *prompt, char **ln)
{
	char		*buf;
	size_t		len;
	int			st;

	if (fd != 0 || !isatty(fd) || rl_rawmode(fd))
		return (rl_readnotty(fd, ln));
	ft_write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	signal(SIGWINCH, rd_sigwinch);
	if (!g_screen_init && rl_screenget(g_screen) < 0)
		st = WUT;
	else if (!(st = rl_editln(prompt, &len, &buf, 0)) && len > 1)
		*ln = rl_histadd(buf, len);
	g_screen_init = 1;
	rl_offmode(fd);
	return (st);
}

int				rl_catline(int fd, char c, char **ln, char **it)
{
	char		*buf;
	size_t		len;
	int			st;

	if (fd != 0 || !isatty(fd) || rl_rawmode(fd))
		return (rl_readnotty(fd, it));
	ft_write(STDOUT_FILENO, "\033[31m>\033[0m ", 2);
	signal(SIGWINCH, rd_sigwinch);
	if (!g_screen_init && rl_screenget(g_screen) < 0)
		st = WUT;
	else if (!(st = rl_editln("\033[31m>\033[0m ", &len, &buf, 1)) && len > 1)
		*it = rl_histcat(buf, len, c, ln);
	g_screen_init = 1;
	rl_offmode(fd);
	return (st);
}

inline int		rl_reprint(void)
{
	if (g_mode == RL_INSERT)
	{
		rl_editprint();
		return (YEP);
	}
	return (NOP);
}
