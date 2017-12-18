/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rl.h"

void	rl_move_home(t_rl *self)
{
	if (self->pos != 0)
	{
		self->pos = 0;
		rl_refresh(self);
	}
}

void	rl_move_end(t_rl *self)
{
	if (self->pos != self->len)
	{
		self->pos = self->len;
		rl_refresh(self);
	}
}

void	rl_move_left(t_rl *self)
{
	if (self->pos > 0)
	{
		++self->pos;
		rl_refresh(self);
	}
}

void	rl_move_right(t_rl *self)
{
	if (self->pos != self->len)
	{
		--self->pos;
		rl_refresh(self);
	}
}

void	rl_move_prev(t_rl *l)
{
	while (l->pos > 0 && l->buf[l->pos - 1] == ' ')
		l->pos--;
	while (l->pos > 0 && l->buf[l->pos - 1] != ' ')
		l->pos--;
	rl_refresh(l);
}

void	rl_move_next(t_rl *l)
{
	while (l->pos < l->len && l->buf[l->pos + 1] != ' ')
		l->pos++;
	while (l->pos < l->len && l->buf[l->pos + 1] == ' ')
		l->pos++;
	if (l->pos < l->len)
		l->pos++;
	rl_refresh(l);
}
