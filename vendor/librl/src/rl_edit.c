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
#define K_UP "\x1b\x5b\x41"
#define K_DOWN "\x1b\x5b\x42"
#define K_RGT "\x1b\x5b\x43"
#define K_LEFT "\x1b\x5b\x44"
#define K_CTRL_UP "\x1b\x5b\x31\x3b\x35\x41"
#define K_CTRL_DOWN "\x1b\x5b\x31\x3b\x35\x42"
#define K_CTRL_RIGHT "\x1b\x5b\x31\x3b\x35\x43"
#define K_CTRL_LEFT "\x1b\x5b\x31\x3b\x35\x44"
#define K_HOME "\x1b\x5b\x48"
#define K_END "\x1b\x5b\x46"
#define K_CTRL_Y "\x19"

static int		rl_return(t_rl *self, char const *key, int rd)
{
	(void)key;
	(void)rd;
	free(self->hist.buf[--self->hist.len]);
	if (self->ml && self->pos != self->len)
	{
		self->pos = self->len;
		rl_refresh(self);
	}
	return (NOP);
}

static int		rl_delete(t_rl *self, char const *key, int rd)
{
	(void)key;
	if (rd == 4 && (self->len > 0 && self->pos < self->len))
	{
		ft_memmove(self->buf + self->pos, self->buf + self->pos + 1,
			(size_t)(self->len - self->pos - 1));
		self->buf[--self->len] = '\0';
	}
	else if (rd == 1 && (self->pos > 0 && self->len > 0)) {
		ft_memmove(self->buf + self->pos - 1, self->buf + self->pos,
			(size_t)(self->len - self->pos));
		--self->pos;
		self->buf[--self->len] = '\0';
	}
	rl_refresh(self);
	return (YEP);
}

static int		rl_move(t_rl *self, char const *k, int n)
{
	if ((n == 1 && *k == *K_CTRL_B) || (n == 3 && !ft_memcmp(K_LEFT, k, 3)))
		self->pos > 0 ? --self->pos : 0;
	else if ((n == 1 && *k == *K_CTRL_F) || (n == 3 && !ft_memcmp(K_RGT, k, 3)))
		self->pos != self->len ? ++self->pos : 0;
	else if (n == 3 && !ft_memcmp(K_UP, k, 3))
		rl_hist_next(self, 1);
	else if (n == 3 && !ft_memcmp(K_DOWN, k, 3))
		rl_hist_next(self, -1);
	else if (n == 3 && !ft_memcmp(K_HOME, k, 3))
		self->pos != 0 ? self->pos = 0 : 0;
	else if (n == 3 && !ft_memcmp(K_END, k, 3))
		self->pos != self->len ? self->pos = self->len : 0;
	else if (n == 6 && !ft_memcmp(K_CTRL_LEFT, k, 6))
		rl_move_prev(self);
	else if (n == 6 && !ft_memcmp(K_CTRL_RIGHT, k, 6))
		rl_move_next(self);
	else if (n == 6 && !ft_memcmp(K_CTRL_UP, k, 6))
		self->pos > self->cols ? self->pos -= self->cols : 0;
	else if (n == 6 && !ft_memcmp(K_CTRL_DOWN, k, 6))
		rl_move_down(self);
	rl_refresh(self);
	return (YEP);
}

static int		rl_ctrl(t_rl *self, char const *key, int rd)
{
	int	aux;

	(void)rd;
	if (*key == *K_CTRL_D && self->len > 0)
		rl_delete(self, K_DELETE, 4);
	else if (*key == *K_CTRL_D)
	{
		free(self->hist.buf[--self->hist.len]);
		return (WUT);
	}
	else if (*key == *K_CTRL_T && self->pos > 0 && self->pos < self->len)
	{
		aux = self->buf[self->pos - 1];
		self->buf[self->pos - 1] = self->buf[self->pos];
		self->buf[self->pos] = (char)aux;
		if (self->pos != self->len - 1)
			++self->pos;
		rl_refresh(self);
	}
	return (NOP);
}

static t_rl_bind	g_insert_binding[] =
{
	{1, K_RETURN, rl_return},
	{1, K_ENTER, rl_return},
	{1, K_BACKSPACE, rl_delete},
	{1, K_CTRL_A, NULL},
	{1, K_CTRL_B, rl_move},
	{1, K_CTRL_D, rl_ctrl},
	{1, K_CTRL_E, NULL},
	{1, K_CTRL_F, rl_move},
	{1, K_CTRL_H, rl_delete},
	{1, K_TAB, NULL},
	{1, K_CTRL_P, NULL},
	{1, K_CTRL_R, NULL},
	{1, K_CTRL_T, rl_ctrl},
	{1, K_CTRL_U, NULL},
	{3, K_LEFT, rl_move},
	{3, K_RGT, rl_move},
	{3, K_UP, rl_move},
	{3, K_DOWN, rl_move},
	{3, K_HOME, rl_move},
	{3, K_END, rl_move},
	{4, K_DELETE, rl_delete},
	{6, K_CTRL_UP, rl_move},
	{6, K_CTRL_DOWN, rl_move},
	{6, K_CTRL_RIGHT, rl_move},
	{6, K_CTRL_LEFT, rl_move},
	{0, NULL, NULL},
};

static void	rl_insert(t_rl *self, char c)
{
	if (self->len != self->pos)
		ft_memmove(self->buf + self->pos + 1, self->buf + self->pos,
			(size_t) (self->len - self->pos));
	self->buf[self->pos] = c;
	self->buf[++self->len] = '\0';
	++self->pos;
	rl_refresh(self);
}

int			rl_edit(t_rl *self)
{
	int			st;
	char		key[6];
	ssize_t		rd;
	t_rl_bind	*b;

	rl_hist_add(self, "");
	while ((rd = ft_read(self->ifd, key, 6)) > 0)
	{
		b = g_insert_binding - 1;
		st = 1;
		while ((++b)->key)
			if (rd == b->rd && !ft_memcmp(b->key, key, (size_t)rd))
			{
				if (!b->cb || (st = b->cb(self, key, (int)rd)) == 0)
					break ;
				return (st < 0 ? WUT : self->len);
			}
		if (st && rd == 1 && !ft_iscntrl(*key) && ft_isascii(*key))
			rl_insert(self, *key);
		else if (st)
		{
			char *s = key;

			dprintf(2, "\"");
			while (*s && rd--)
				dprintf(2, "\\x%x", *s++);
			dprintf(2, "\"\n");
		}
	}
	return (self->len);
}
