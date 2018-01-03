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

char			*sh_readln(int fd, char *prompt)
{
	t_histln	*ln;
	size_t		plen;

	if (fd != 0 || !isatty(fd) || sh_rawmode(fd))
		return (sh_readnotty(fd));
	ln = sh_histpush("");
	ft_write(STDIN_FILENO, prompt, plen = ft_strlen(prompt));
	signal(SIGWINCH, rd_sigwinch);
	if (sh_screenget(g_screen, fd, STDOUT_FILENO) < 0)
		return (rd_finalize(NULL, 0));
	if (sh_editln(&ln->edit, prompt, plen) || !ln->edit.len)
		return (rd_finalize(NULL, 0));
	if (!ln->cap || ln->cap < ln->edit.len)
	{
		if (ln->cap && ln->cap < ln->edit.len)
			free(ln->buf);
		ln->cap = pow2_next16(ln->edit.len);
		ln->buf = ft_malloc(ln->cap * sizeof(char));
	}
	ft_memcpy(ln->buf, ln->edit.buf, ln->len = ln->edit.len);
	ln->buf[ln->len] = '\0';
	return (rd_finalize(ln->buf, 0));
}

char			*sh_readcat(int fd, char *prompt, char c)
{
	t_histln	*ln;
	size_t		plen;
	uint16_t	nlen;
	uint16_t	middle;
	char		*buf;

	if (fd != 0 || !isatty(fd) || sh_rawmode(fd))
		return (sh_readnotty(fd));
	ln = sh_histln();
	ln->edit.len = 0;
	ln->edit.idx = 0;
	ln->edit.row = 0;
	ln->edit.rows = 0;
	*ln->edit.buf = '\0';
	ft_write(STDIN_FILENO, prompt, plen = ft_strlen(prompt));
	if (sh_screenget(g_screen, STDIN_FILENO, STDOUT_FILENO) < 0)
		return (rd_finalize(NULL, 0));
	if (sh_editln(&ln->edit, prompt, plen) || !ln->edit.len)
		return (rd_finalize(NULL, 0));
	middle = (uint16_t)(ln->len + (c <= 0 ? c : 1));
	if (ln->cap < (nlen = (uint16_t)(ln->edit.len + middle)))
	{
		ln->cap = pow2_next16((uint16_t)(nlen + 1));
		buf = ft_malloc(ln->cap * sizeof(char));
		buf = ft_memcpy(buf, ln->buf, (size_t)middle);
		free(ln->buf);
		ln->buf = buf;
	}
	c > 0 ? (uint16_t)(*(ln->buf + middle - 1) = c) : (c < 0 ? --middle : 0);
	ft_memcpy(ln->buf + middle, ln->edit.buf, ln->edit.len);
	ln->len = nlen;
	ln->buf[ln->len] = '\0';
	return (rd_finalize(ln->buf + middle, 0));
}
