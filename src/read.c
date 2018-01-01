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

#include "msh/read.h"
#include "msh/edit.h"

t_rmode			g_mode;
TTY				g_orig_mode;
TTY				g_raw_mode;
uint16_t		g_cols;
uint16_t		g_pos;

static char		*rd_finalize(char *result, int eno)
{
	if (eno)
		ENO_THROW(WUT, eno);
	sh_offmode(STDIN_FILENO);
	return (result);
}

extern char		*sh_readln(int fd, char *prompt)
{
	t_histln	*ln;
	int			st;
	size_t		plen;

	if (fd != 0 || !isatty(fd) || sh_rawmode(fd))
		return (sh_readnotty(fd));
	ln = sh_histpush("");
	ft_write(STDIN_FILENO, prompt, plen = ft_strlen(prompt));
	if ((st = sh_screenwidth(fd, STDOUT_FILENO)) <= 0)
		return (rd_finalize(NULL, 0));
	g_cols = (uint16_t)st;
	if (sh_editln(ln, prompt, plen) || !ln->edit.len)
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

extern char	*sh_readcat(int fd, char *prompt, char c)
{
	t_histln	*ln;
	int			st;
	size_t		plen;
	uint16_t	nlen;
	uint16_t	middle;
	char		*buf;

	if (fd != 0 || !isatty(fd) || sh_rawmode(fd))
		return (sh_readnotty(fd));
	ln = sh_histln();
	ln->edit.len = 0;
	ln->edit.idx = 0;
	*ln->edit.buf = '\0';
	ft_write(STDIN_FILENO, prompt, plen = ft_strlen(prompt));
	if ((st = sh_screenwidth(fd, STDOUT_FILENO)) <= 0)
		return (rd_finalize(NULL, 0));
	g_cols = (uint16_t)st;
	if (sh_editln(ln, prompt, plen) || !ln->edit.len)
		return (rd_finalize(NULL, 0));
	middle = (uint16_t)(ln->len + (c < 0 ? c : 1));
	if (ln->cap < (nlen = (uint16_t)(ln->edit.len + middle + 1)))
	{
		free(ln->buf);
		ln->cap = pow2_next16(nlen);
		buf = ft_malloc(ln->cap * sizeof(char));
		ln->buf = ft_memcpy(buf, ln->buf, (size_t)middle);
	}
	c > 0 ? (uint16_t)(*(ln->buf + middle - 1) = c) : --middle;
	ft_strncpy(ln->buf + middle, ln->edit.buf, ln->edit.len);
	ln->len = nlen;
	ln->buf[ln->len] = '\0';
	return (rd_finalize(ln->buf + middle, 0));
}
