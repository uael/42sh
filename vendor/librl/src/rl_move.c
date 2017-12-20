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

void	rl_move_down(t_rl *self)
{
	if (self->pos + self->cols <= self->len)
		self->pos += self->cols;
	else if (self->pos / self->cols < self->len / self->cols)
		self->pos = self->len;
	rl_refresh(self);
}

void	rl_move_prev(t_rl *self)
{
	while (self->pos > 0 && self->buf[self->pos - 1] == ' ')
		self->pos--;
	while (self->pos > 0 && self->buf[self->pos - 1] != ' ')
		self->pos--;
	rl_refresh(self);
}

void	rl_move_next(t_rl *self)
{
	while (self->pos < self->len && self->buf[self->pos + 1] != ' ')
		self->pos++;
	while (self->pos < self->len && self->buf[self->pos + 1] == ' ')
		self->pos++;
	if (self->pos < self->len)
		self->pos++;
	rl_refresh(self);
}
