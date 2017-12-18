/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_ctor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rl.h"

int		rl_ctor(t_rl *self, int ifd, int ofd, t_bool ml)
{
	ft_memset(self, 0, sizeof(t_rl));
	self->ml = ml;
	self->ofd = ofd;
	if (!isatty(self->ifd = ifd))
		self->mode = RL_NOTTY;
	else
	{
		if (tcgetattr(self->ifd, &self->orig) == -1)
			return (ENO_THROW(WUT, ENOTTY));
		self->raw = self->orig;
		self->raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | OPOST);
		self->raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		self->raw.c_cflag |= (CS8);
		self->raw.c_cc[VMIN] = 1;
		self->raw.c_cc[VTIME] = 0;
		self->mode = RL_OFF;
	}
	return (YEP);
}

void	rl_dtor(t_rl *self)
{
	if (self->mode == RL_INSERT)
	{
		if (tcsetattr(self->ifd, TCSADRAIN, &self->orig) == -1)
			return ;
		self->mode = RL_OFF;
	}
}
