/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_refresh.c                                       :+:      :+:    :+:   */
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
	t_ofs	*obuf;
	int		rows;
	int		rpos;
	int		rpos2;
	int		col;
	int		old_rows;
	int		j;

	ft_ofsctor(obuf = alloca(sizeof(t_ofs)), self->ofd);
	rows = (self->plen + self->len + self->cols - 1) / self->cols;
	rpos = (self->plen + self->oldpos + self->cols) / self->cols;
	old_rows = self->mrows;
	if (rows > self->mrows)
		self->mrows = rows;
	if (old_rows-rpos > 0)
		ft_ofswrf(obuf, "\x1b[%dB", old_rows - rpos);
	for (j = 0; j < old_rows-1; j++)
		ft_ofswr(obuf, "\r\x1b[0K\x1b[1A", sizeof("\r\x1b[0K\x1b[1A") - 1);
	ft_ofswr(obuf, "\r\x1b[0K", sizeof("\r\x1b[0K") - 1);
	ft_ofswr(obuf, self->prompt, (size_t)self->plen);
	ft_ofswr(obuf, self->buf, (size_t)self->len);
	if (self->pos && self->pos == self->len &&
		(self->pos + self->plen) % self->cols == 0)
	{
		ft_ofswr(obuf, "\n", 1);
		rows++;
		if (rows > self->mrows)
			self->mrows = rows;
	}
	rpos2 = (self->plen + self->pos + self->cols) / self->cols;
	if (rows-rpos2 > 0)
		ft_ofswrf(obuf, "\x1b[%dA", rows - rpos2);
	col = (self->plen + self->pos) % self->cols;
	if (col)
		ft_ofswrf(obuf, "\r\x1b[%dC", col);
	else
		ft_ofswr(obuf, "\r", 1);
	self->oldpos = self->pos;
	ft_ofsflush(obuf);
}
