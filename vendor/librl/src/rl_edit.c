/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "rl.h"

#define K_BACKSPACE "\x7f"
#define K_DELETE "\x1b\x5b\x33\x7e"
#define K_CTRL_A "\x1"
#define K_CTRL_B "\x2"
#define K_CTRL_D "\x4"
#define K_CTRL_E "\x5"
#define K_CTRL_F "\x6"
#define K_CTRL_H "\x8"
#define K_TAB "\x9"
#define K_RETURN "\xa"
#define K_CTRL_K "\xb"
#define K_CTRL_L "\xc"
#define K_ENTER "\xd"
#define K_CTRL_P "\x10"
#define K_CTRL_R "\x12"
#define K_CTRL_T "\x14"
#define K_CTRL_U "\x15"
#define K_ALT_B "\x1b\x62"
#define K_ALT_F "\x1b\x66"
#define K_UP "\x1b\x5b\x41"
#define K_DOWN "\x1b\x5b\x42"
#define K_RIGHT "\x1b\x5b\x43"
#define K_LEFT "\x1b\x5b\x44"
#define K_CTRL_UP "\x1b\x5b\x31\x3b\x35\x41"
#define K_CTRL_DOWN "\x1b\x5b\x31\x3b\x35\x42"
#define K_CTRL_RIGHT "\x1b\x5b\x31\x3b\x35\x43"
#define K_CTRL_LEFT "\x1b\x5b\x31\x3b\x35\x44"
#define K_HOME "\x1b\x5b\x48"
#define K_END "\x1b\x5b\x46"
#define K_CTRL_Y "\x19"

void	rl_backspace(t_rl *self)
{
	(void)self;
}

void	rl_delete(t_rl *self)
{
	(void)self;
}

int		rl_edit(t_rl *self)
{
	int		aux;
	char	buf[6];
	ssize_t	rd;

	rl_hist_add(self, "");
	while ((rd = ft_read(self->ifd, buf, 6)))
		if (rd < 0)
			break ;
		else if (rd == 1 && (*buf == *K_RETURN || *buf == *K_ENTER))
		{
			free(self->hist.buf[--self->hist.len]);
			if (self->ml)
				rl_move_end(self);
			return self->len;
		}
		else if (rd == 1 && (*buf == *K_BACKSPACE || *buf == *K_CTRL_H))
			rl_backspace(self);
		else if ((rd == 1 && *buf == *K_CTRL_D) ||
			(rd == 4 && !ft_memcmp(K_DELETE, buf, 4)))
		{
			if (self->len <= 0)
				return -1;
			rl_delete(self);
		}
		else if (rd == 1 && *buf == *K_CTRL_T)
		{
			if (self->pos > 0 && self->pos < self->len)
			{
				aux = self->buf[self->pos - 1];
				self->buf[self->pos - 1] = self->buf[self->pos];
				self->buf[self->pos] = (char)aux;
				if (self->pos != self->len - 1)
					++self->pos;
				rl_refresh(self);
			}
		}
		else if ((rd == 1 && *buf == *K_CTRL_B) ||
			(rd == 3 && !ft_memcmp(K_LEFT, buf, 3)))
			rl_move_left(self);
		else if ((rd == 1 && *buf == *K_CTRL_F) ||
			(rd == 3 && !ft_memcmp(K_RIGHT, buf, 3)))
			rl_move_right(self);
		else if (rd == 3 && !ft_memcmp(K_UP, buf, 3))
			rl_hist_next(self, 1);
		else if (rd == 3 && !ft_memcmp(K_DOWN, buf, 3))
			rl_hist_next(self, -1);
		else if (rd == 3 && !ft_memcmp(K_HOME, buf, 3))
			rl_move_home(self);
		else if (rd == 3 && !ft_memcmp(K_END, buf, 3))
			rl_move_end(self);
		else if (rd == 6 && !ft_memcmp(K_CTRL_LEFT, buf, 6))
			rl_move_prev(self);
		else if (rd == 6 && !ft_memcmp(K_CTRL_RIGHT, buf, 6))
			rl_move_next(self);
		else if (rd == 6 && !ft_memcmp(K_CTRL_UP, buf, 6))
			rl_move_up(self);
		else if (rd == 6 && !ft_memcmp(K_CTRL_DOWN, buf, 6))
			rl_move_down(self);
		else if (rd > 1 || ft_iscntrl(*buf) || !ft_isascii(*buf))
		{
			char *s = buf;

			dprintf(2, "\"");
			while (*s && rd--)
				dprintf(2, "\\x%x", *s++);
			dprintf(2, "\"\n");
		}
		else
		{
			if (self->len != self->pos)
				ft_memmove(self->buf + self->pos + 1, self->buf + self->pos,
					(size_t)(self->len - self->pos));
			self->buf[self->pos] = *buf;
			self->buf[++self->len] = '\0';
			++self->pos;
			rl_refresh(self);
		}
	return (self->len);
}
