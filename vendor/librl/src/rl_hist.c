/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_hist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rl.h"

char		*rl_hist_add(struct s_rl *self, char const *line)
{
	size_t	sz;
	char	**it;

	if (self->hist.len && !ft_strcmp(line, self->hist.buf[self->hist.len - 1]))
		return (self->hist.buf[self->hist.len - 1]);
	if (self->hist.len && self->hist.len == self->hist.max)
	{
		free(self->hist.buf[0]);
		ft_bufshift(self->hist.buf, 1, (size_t)self->hist.len, sizeof(char *));
		--self->hist.len;
	}
	sz = ft_strlen(line);
	if (!self->hist.buf)
		self->hist.buf = ft_malloc(self->hist.max * sizeof(char *));
	it = ft_bufat(self->hist.buf, (size_t)self->hist.len++, sizeof(char *));
	return (*it = ft_memcpy(ft_malloc((sz + 1) * sizeof(char)), line, sz + 1));
}

int			rl_hist_load(struct s_rl *self, char const *filename)
{
	t_ifs	*in;
	ssize_t	rd;
	char	*ln;

	if (ft_ifsopen(in = alloca(sizeof(t_ifs)), filename) < 0)
		return (WUT);
	while ((rd = ft_ifschr(in, 0, '\n', &ln)))
	{
		if (rd < 0)
			return (WUT);
		while (*(ln - 1) == '\r' && rd)
			if ((rd = ft_ifschr(in, (size_t)rd, '\n', NULL)) < 0)
				return (WUT);
		ln[rd] = '\0';
		rl_hist_add(self, ln);
		ft_ifsrd(in, NULL, (size_t)rd);
	}
	if (ft_ifsclose(in))
		return (THROW(WUT));
	return (YEP);
}

int			rl_hist_save(struct s_rl *self, char const *filename)
{
	t_ofs	*out;
	char	**line;
	char	**end;

	if (!(line = self->hist.buf))
		return (YEP);
	if (ft_ofsopen(out = alloca(sizeof(t_ofs)), filename) < 0)
		return (THROW(WUT));
	end = self->hist.buf + self->hist.len;
	while (line != end)
		ft_ofswrs(out, *line++);
	if (ft_ofsclose(out))
		return (THROW(WUT));
	return (YEP);
}

void	rl_hist_next(t_rl *self, int dir)
{
	if (self->hist.len > 1)
	{
		free(self->hist.buf[self->hist.len - 1 - self->hist.idx]);
		self->hist.buf[self->hist.len - 1 - self->hist.idx] =
			ft_strdup(self->buf);
		self->hist.idx += dir;
		if (self->hist.idx < 0)
			self->hist.idx = 0;
		else if (self->hist.idx >= self->hist.len)
			self->hist.idx = self->hist.len - 1;
		else
		{
			ft_strcpy(self->buf,
				self->hist.buf[self->hist.len - 1 - self->hist.idx]);
			self->len = (int)ft_strlen(self->buf);
			self->pos = self->len;
			rl_refresh(self);
		}
	}
}
