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

#include "msh/read.h"
#include "msh/shell.h"

t_rmode			g_mode;
TTY				g_orig_mode;
TTY				g_raw_mode;

static char		*rd_finalize(char *result, int eno)
{
	if (eno)
		ENO_THROW(WUT, eno);
	sh_offmode(STDIN_FILENO);
	return (result);
}

void			rd_sigwinch(int signo)
{
	(void)signo;
	sh_screenget(g_screen, STDIN_FILENO, STDOUT_FILENO);
}

void			sh_readfinalize(int fd)
{
	if (isatty(fd))
		return (sh_ttyfinalize(fd));
	sh_nottyfinalize(fd);
}

void			sh_readexit(void)
{
	if (g_shfd >= 0)
	{
		sh_readfinalize(g_shfd);
		if (isatty(g_shfd))
			sh_ttyexit();
		sh_nottyexit();
	}
}

char			*sh_readln(int fd, char *prompt)
{
	char		*ln;
	size_t		len;

	if (fd != 0 || !isatty(fd) || sh_rawmode(fd))
		return (sh_readnotty(fd));
	ft_write(STDIN_FILENO, prompt, ft_strlen(prompt));
	signal(SIGWINCH, rd_sigwinch);
	if (sh_screenget(g_screen, fd, STDOUT_FILENO) < 0)
		return (rd_finalize(NULL, 0));
	if (!(ln = sh_editln(prompt, &len)) || !len)
		return (rd_finalize(NULL, 0));
	return (rd_finalize(len == 1 && *ln == '\n' ? ln : sh_histadd(ln, len), 0));
}

char			*sh_readcat(int fd, char *prompt, char c, char **out)
{
	char		*ln;
	size_t		len;

	if (fd != 0 || !isatty(fd) || sh_rawmode(fd))
		return (sh_readnotty(fd));
	ft_write(STDIN_FILENO, prompt, ft_strlen(prompt));
	signal(SIGWINCH, rd_sigwinch);
	if (sh_screenget(g_screen, fd, STDOUT_FILENO) < 0)
		return (rd_finalize(NULL, 0));
	if (!(ln = sh_editln(prompt, &len)) || !len)
		return (rd_finalize(NULL, 0));
	return (rd_finalize(sh_histcat(ln, len, c, out), 0));
}
