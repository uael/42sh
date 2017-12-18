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
	char	buf[RL_MAX_LINE + 1];
	char	*eol;
	char	*line;
	ssize_t	rd;

	eol = NULL;
	while ((!self->buf || (eol || !(eol = ft_strchr(self->buf, '\n')))))
		if ((rd = read(self->ifd, buf, RL_MAX_LINE)) < 0 && errno != EINTR)
			return (rl_throw(0));
		else if (!rd || (rd > 0 && (eol = ft_strchr(ft_memcpy(*(char **)
			ft_bufpush(&self->buf, &self->len, (size_t)rd, sizeof(char)), buf,
			(size_t)rd),'\n'))))
			break ;
	if (!(rd = eol ? (eol - self->buf + 1) : (ssize_t)self->len))
		return (NULL);
	rd += (ssize_t)(eol ? 1 : 0);
	line = ft_memcpy(ft_malloc((size_t)rd * sizeof(char)), self->buf,
		(size_t)rd * sizeof(char));
	line[rd] = '\0';
	ft_bufshift(self->buf, &self->len, (size_t)rd, sizeof(char));
	return (line);
}

static char	*rl_tty(t_rl *self)
{
	char	buf[RL_MAX_LINE + 1];
	int		len;

	if (self->mode == RL_OFF)
	{
		if (tcsetattr(self->ifd, TCSADRAIN, &self->raw) < 0)
			return (rl_throw(ENOTTY));
		self->mode = RL_INSERT;
	}
	self->buf = ft_memset(buf, 0, RL_MAX_LINE + 1);
	self->mlen = RL_MAX_LINE;
	len = rl_edit(self);
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
	if (write(self->ofd, prompt, self->plen = ft_strlen(prompt)) < 0)
		return (rl_throw(0));
	self->prompt = prompt;
	self->len = 0;
	self->hist.search = 0;
	self->hist.idx = 0;
	self->pos = 0;
	self->cols = rl_cols(self->ifd, self->ofd);
	return (rl_tty(self));
}

char		*rl_readnext(t_rl *self, char const *prompt)
{
	(void)self;
	(void)prompt;
	return (NULL);
}
