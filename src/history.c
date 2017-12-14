/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 16:02:50 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/reduce.h"

int	sh_history_init(t_sh *self, char *filename)
{
	t_ifstream	ifs;
	char		*ln;
	char 		*path;
	int			fd;

	if (!(path = ft_getenv(self->env.buf, "HOME")))
		return (NOP);
	path = ft_join(path, filename, '/');
	while ((fd = open(path, O_RDONLY, S_IRUSR | S_IWUSR)) < 0)
		if (errno != EINTR)
		{
			free(path);
			return (NOP);
		}
	FT_INIT(&ifs, t_ifstream);
	ifs.fd = fd;
	ifs.filename = path;
	while ((ln = ft_ifstream_getl(&ifs, '\n')))
		ft_dqstr_pushc(&self->history, ln);
	if (errno)
		return (WUT);
	free(path);
	return (YEP);
}

int	sh_history_save(t_sh *self, char *filename)
{
	t_ofstream	ofs;
	char		**it;
	char 		*path;
	int			fd;

	if (!(path = ft_getenv(self->env.buf, "HOME")))
		return (NOP);
	path = ft_join(path, filename, '/');
	while ((fd = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		if (errno != EINTR)
		{
			free(path);
			return (NOP);
		}
	FT_INIT(&ofs, t_ofstream);
	ofs.fd = fd;
	ofs.filename = path;
	if ((it = ft_dqstr_begin(&self->history)))
		while (it != ft_dqstr_end(&self->history))
			ft_ofstream_puts(&ofs, *it++);
	free(path);
	ft_ofstream_close(&ofs);
	return (YEP);
}
