/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:14 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:29:11 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/term.h"

static int		term_init_history(t_term *self, char *history)
{
	t_ifstream	ifs;
	char		*ln;
	int			fd;

	self->history_fn = history;
	ft_vstr_ctor(&self->history);
	while ((fd = open(history, O_RDONLY, S_IRUSR | S_IWUSR)) < 0)
		if (errno != EINTR)
			return (YEP);
	FT_INIT(&ifs, t_ifstream);
	ifs.fd = fd;
	ifs.filename = history;
	while ((ln = ft_ifstream_getl(&ifs, '\n')))
		ft_vstr_pushc(&self->history, ft_strdup(ln));
	self->hcurs = ft_vstr_size(&self->history);
	ft_ifstream_close(&ifs);
	return (YEP);
}

static int		term_ctor_tty(t_term *self, char **env, char *history)
{
	char		*term;
	char		*ttyn;

	if (!(term = ft_getenv(env, "TERM")))
		term = "xterm";
	if (!(ttyn = ttyname(STDIN_FILENO)) &&
		!(ttyn = ttyname(STDOUT_FILENO)) &&
		!(ttyn = ttyname(STDERR_FILENO)))
		return (ENO_THROW(WUT, ENOTTY));
	if (tgetent(NULL, term) <= 0 ||
		(self->fd = open(ttyn, O_RDWR, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(WUT));
	tcgetattr(self->fd, &self->on);
	ft_memcpy(&self->off, &self->on, sizeof(t_termios));
	self->on.c_lflag &= ~(ICANON | ECHO);
	self->on.c_cc[VMIN] = 1;
	self->on.c_cc[VTIME] = 10;
	self->mode = TERM_OFF;
	return (term_init_history(self, history));
}

inline int		ft_term_ctor(t_term *self, char **env, char *history)
{
	FT_INIT(self, t_term);
	if (isatty(STDIN_FILENO))
		return (term_ctor_tty(self, env, history));
	self->fd = STDIN_FILENO;
	self->mode = TERM_NOTTY;
	return (YEP);
}

inline void		ft_term_dtor(t_term *self)
{
	t_ofstream	ofs;
	char		**it;
	int			fd;

	if (self->mode == TERM_NOTTY)
		ft_istream_close(g_cin);
	else
	{
		while ((fd = open(self->history_fn,
			O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
			if (errno != EINTR)
				return ;
		FT_INIT(&ofs, t_ofstream);
		ofs.fd = fd;
		ofs.filename = self->history_fn;
		if ((it = ft_vstr_begin(&self->history)))
			while (it != ft_vstr_end(&self->history))
				ft_ofstream_puts(&ofs, *it++);
		ft_ofstream_close(&ofs);
		if (close(self->fd))
			THROW(WUT);
	}
}
