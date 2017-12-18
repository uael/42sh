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

void	rl_refresh(t_rl *self)
{
	(void)self;
}

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

	while ((nr = read(self->ifd, cbuf, 1)))
		if (nr < 0 && errno != EINTR)
			return (THROW((int)self->len));
		else if (nr < 0)
			continue ;
		else if ((c = cbuf[0]) == 13)
		{
			if (self->ml)
				rl_move_end(self);
			return (int)self->len;
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
			if (read(self->ifd, seq, 1) == -1)
				continue ;
			c = ft_tolower(seq[0]);
			if (c == 'b')
				rl_move_prev(self);
			else if (c == 'f')
				rl_move_next(self);
		}
	return (NULL);
}
