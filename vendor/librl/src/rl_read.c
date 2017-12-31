/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rl.h"

static char	*rl_notty(t_rl *self)
{
	char	*ln;
	ssize_t	rd;

	if ((rd = ft_ifschr(&self->in, 0, '\n', &ln)) <= 0)
		return (NULL);
	ln = ft_memcpy(ft_malloc((rd + 1) * sizeof(char)), ln, (size_t)rd);
	ln[rd] = '\0';
	ft_ifsrd(&self->in, NULL, (size_t)rd);
	return (ln);
}

static char	*rl_tty(t_rl *self)
{
	char	buf[RL_MAX_LINE + 1];
	int		len;

	if (self->mode == RL_OFF)
	{
		if (tcsetattr(self->ifd, TCSADRAIN, &self->raw) < 0)
		{
			ENO_THROW(WUT, ENOTTY);
			return (NULL);
		}
		self->mode = RL_INSERT;
	}
	self->buf = ft_memset(buf, 0, RL_MAX_LINE + 1);
	self->mlen = RL_MAX_LINE;
	len = rl_edit(self);
	ft_write(self->ofd, "\n", 1);
	if (self->mode != RL_OFF)
	{
		if (tcsetattr(self->ifd, TCSADRAIN, &self->orig) == -1)
			return (NULL);
		self->mode = RL_OFF;
	}
	return (len < 0 ? NULL : rl_hist_add(self, buf));
}

char		*rl_readline(t_rl *self, char const *prompt)
{
	if (self->mode == RL_NOTTY)
		return (rl_notty(self));
	if (ft_write(self->ofd, prompt,
		(size_t)(self->plen = (int)ft_strlen(prompt))) < 0)
		return (NULL);
	self->prompt = prompt;
	self->len = 0;
	self->hist.search = 0;
	self->hist.idx = 0;
	self->pos = 0;
	self->mrows = 0;
	self->oldpos = 0;
	self->cols = rl_cols(self->ifd, self->ofd);
	return (rl_tty(self));
}

char		*rl_readnext(t_rl *self, char const *prompt)
{
	(void)self;
	(void)prompt;
	return (NULL);
}
