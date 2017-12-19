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

#include "rl.h"

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
	int		c;
	int		aux;
	char	cbuf[32];
	char	seq[3];
	ssize_t	nr;

	while ((nr = ft_read(self->ifd, cbuf, 1)))
		if (nr < 0)
			break ;
		else if ((c = cbuf[0]) == 13)
		{
			if (self->ml)
				rl_move_end(self);
			return self->len;
		}
		else if (c == 127 || c == 8)
			rl_backspace(self);
		else if (c == 4)
		{
			if (self->len <= 0)
				return -1;
			rl_delete(self);
		}
		else if (c == 20)
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
		else if (c == 2)
			rl_move_left(self);
		else if (c == 6)
			rl_move_right(self);
		else if (c == 27)
		{
			if (ft_read(self->ifd, seq, 1) == -1)
				continue ;
			c = seq[0];
			if ((c | 0x20) == 'b')
				rl_move_prev(self);
			else if ((c | 0x20) == 'f')
				rl_move_next(self);
			else if (c == '0' || c ==  '[')
			{
				if (ft_read(self->ifd, seq + 1, 1) == -1)
					continue ;
				if ((c = seq[1]) == 'C')
					rl_move_right(self);
				else if (c == 'D')
					rl_move_left(self);
				else if (c == 'H')
					rl_move_home(self);
				else if (c == 'F')
					rl_move_end(self);
				else if (ft_isdigit(c))
				{
					if (ft_read(self->ifd, seq + 2, 1) == -1)
						continue ;
					if (seq[2] == '~')
					{
						if (c == '3')
							rl_delete(self);
						else if (c == '1')
							rl_move_home(self);
						else if (c == '4')
							rl_move_end(self);
					}

				}
			}
		}
		else if (!ft_iscntrl(c) && ft_isascii(c) && self->len + 1 < self->mlen)
		{
			if (self->len == self->pos)
			{
				self->buf[self->len] = (char)c;
				self->buf[++self->len] = '\0';
				++self->pos;
				if (self->pos / self->cols < self->cols)
					ft_write(self->ofd, &c, 1);
				else
					rl_refresh(self);
			}
			else
			{
				ft_memmove(self->buf + self->pos + 1, self->buf + self->pos,
					(size_t)(self->len - self->pos));
				self->buf[self->pos] = (char)c;
				self->buf[++self->len] = '\0';
				++self->pos;
				rl_refresh(self);
			}
		}
	return (self->len);
}
