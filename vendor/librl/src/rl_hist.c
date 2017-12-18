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

	if (!(sz = ft_strlen(line)))
		return (NULL);
	if (self->hist.len && !ft_strcmp(line, self->hist.buf[self->hist.len - 1]))
		return (self->hist.buf[self->hist.len - 1]);
	if (self->hist.len == self->hist.max)
	{
		free(self->hist.buf[0]);
		ft_bufshift(self->hist.buf, &self->hist.len, 1, sizeof(char *));
	}
	it = (char **)ft_bufpush(&self->hist.buf, &self->hist.len, sizeof(char),
		sizeof(char *));
	return (*it = ft_memcpy(ft_malloc((sz + 1) * sizeof(char)), line, sz + 1));
}

int			rl_hist_load(struct s_rl *self, char const *filename)
{
	int		fd;
	char	buf[RL_MAX_LINE + 1];
	char	*str;
	ssize_t	rd;
	char	*eol;

	if ((fd = open(filename, O_RDONLY, S_IRUSR | S_IWUSR)) < (rd = 0))
		return (THROW(WUT));
	while ((rd = read(fd, buf + rd, RL_MAX_LINE)))
		if (rd < 0 && errno != EINTR)
			return (THROW(WUT));
		else if (rd > 0)
		{
			str = buf;
			while ((eol = ft_strnchr(str, '\n', (size_t)rd)))
				if (*(eol - 1) != '\r')
				{
					*eol = '\0';
					rl_hist_add(self, str);
					rd -= eol - str;
					str = eol + 1;
				}
			rd > 0 ? ft_memcpy(buf, str, (size_t)rd) : 0;
		}
	return (0);
}

int			rl_hist_save(struct s_rl *self, char const *filename)
{
	int		fd;
	char	**line;
	char	**end;

	if (!(line = self->hist.buf))
		return (YEP);
	if ((fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(WUT));
	end = self->hist.buf + self->hist.len;
	while (line != end)
	{
		write(fd, *line, ft_strlen(*line));
		write(fd, "\n", 1);
		++line;
	}
	if (close(fd))
		return (THROW(WUT));
	return (YEP);
}
