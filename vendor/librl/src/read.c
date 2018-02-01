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
	if (g_mode != RL_OFF && g_mode != RL_NONE)
		rl_editprint();
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
	uint16_t	col;

	if (fd != 0 || !isatty(fd) || rl_rawmode(fd))
		return (rl_readnotty(fd, ln));
	if (!rl_screenpos(NULL, &col) && col > 1)
		ft_puts(STDIN_FILENO, TC_MR"%"TC_ME"\n");
	ft_puts(STDIN_FILENO, prompt);
	signal(SIGWINCH, rd_sigwinch);
	if (!g_screen_init && rl_screenget(g_screen) < 0)
		st = WUT;
	else if (!(st = rl_editln(prompt, &len, &buf, 0)))
		*ln = len > 1 ? rl_histadd(buf, len) : buf;
	g_screen_init = 1;
	rl_offmode(fd);
	if (st == RL_CLR)
		st = YEP;
	return (st <= 0 ? st : OUF);
}

int				rl_catline(int fd, char c, char **ln, char **it)
{
	char		*buf;
	size_t		len;
	int			st;

	if (fd != 0 || !isatty(fd) || rl_rawmode(fd))
	{
		st = rl_readnotty(fd, it);
		*ln = *it;
		return (st);
	}
	ft_puts(STDIN_FILENO, "\033[31m>\033[0m ");
	signal(SIGWINCH, rd_sigwinch);
	if (!g_screen_init && rl_screenget(g_screen) < 0)
		st = WUT;
	else if (!(st = rl_editln("\033[31m>\033[0m ", &len, &buf, 1)))
		*it = len ? rl_histcat(buf, len, c, ln) : buf;
	g_screen_init = 1;
	rl_offmode(fd);
	return (st <= 0 ? st : OUF);
}
