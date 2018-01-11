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

#include <signal.h>
#include <sys/signal.h>

#include "read.h"

t_rmode			g_mode = RL_NONE;
TTY				g_orig_mode;
TTY				g_raw_mode;

static char		*rd_finalize(char *result, int eno)
{
	if (eno)
		ENO_THROW(WUT, eno);
	rl_offmode(STDIN_FILENO);
	return (result);
}

void			rd_sigwinch(int signo)
{
	(void)signo;
	rl_screenget(g_screen, STDIN_FILENO, STDOUT_FILENO);
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

char			*rl_getline(int fd, char *prompt)
{
	char		*ln;
	size_t		len;

	if (fd != 0 || !isatty(fd) || rl_rawmode(fd))
		return (rl_readnotty(fd));
	ft_write(STDIN_FILENO, prompt, ft_strlen(prompt));
	signal(SIGWINCH, rd_sigwinch);
	if (rl_screenget(g_screen, fd, STDOUT_FILENO) < 0)
		return (rd_finalize(NULL, 0));
	if (!(ln = rl_editln(prompt, &len)) || !len)
		return (rd_finalize(NULL, 0));
	return (rd_finalize(len == 1 && *ln == '\n' ? ln : rl_histadd(ln, len), 0));
}

char			*rl_catline(int fd, char *prompt, char c, char **out)
{
	char		*ln;
	size_t		len;

	if (fd != 0 || !isatty(fd) || rl_rawmode(fd))
		return (rl_readnotty(fd));
	ft_write(STDIN_FILENO, prompt, ft_strlen(prompt));
	signal(SIGWINCH, rd_sigwinch);
	if (rl_screenget(g_screen, fd, STDOUT_FILENO) < 0)
		return (rd_finalize(NULL, 0));
	if (!(ln = rl_editln(prompt, &len)) || !len)
		return (rd_finalize(NULL, 0));
	return (rd_finalize(rl_histcat(ln, len, c, out), 0));
}
