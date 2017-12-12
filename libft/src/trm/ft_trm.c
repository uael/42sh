/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:11 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:37:11 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>

#include "libft/trm.h"

#define TRM_USG "%s: Specify a terminal type with `setenv TERM <yourtype>`\n"

int		ft_trm_ctor(t_trm *self)
{
	char		*tnm;
	const char	*dev;

	FT_INIT(self, t_trm);
	if (!(tnm = getenv("TERM")))
		return (ft_retf(NOP, TRM_USG, "select"));
	if (!(dev = ttyname(STDIN_FILENO)))
		dev = ttyname(STDOUT_FILENO);
	if (!dev && !(dev = ttyname(STDERR_FILENO)))
		return (ENO_THROW(WUT, ENOTTY));
	if (tgetent(NULL, tnm) <= 0 || ft_ostream_open(&self->out, dev))
		return (ft_retf(NOP, "%s: %e.\n", "trm", errno));
	ft_du8_ctor(&self->in);
	tcgetattr(self->out.u.file.fd, &self->tty);
	ft_memcpy(&self->tmp, &self->tty, sizeof(t_trmios));
	self->tty.c_lflag &= ~ICANON;
	self->tty.c_lflag &= ~ECHO;
	self->tty.c_cc[VMIN] = 1;
	self->tty.c_cc[VTIME] = 100;
	ft_trm_on(self);
	ft_trm_refresh(self);
	return (YEP);
}

void		ft_trm_dtor(t_trm *self)
{
	ft_trm_off(self);
	ft_ostream_close(&self->out);
	ft_du8_dtor(&self->in, NULL);
	FT_INIT(self, t_trm);
}

inline void	ft_trm_refresh(t_trm *self)
{
	struct winsize	w;

	if (!isatty(self->out.u.file.fd))
		return ;
	if (ioctl(self->out.u.file.fd, TIOCGWINSZ, &w))
		ft_fatal(NOP, (t_dtor)ft_trm_dtor, self, "ioctl: %e", errno);
	self->w = w.ws_col;
	self->h = w.ws_row;
}

/*
** todo: check for tgetstr("*", NULL), TERM=i100 for ex
*/

inline void	ft_trm_clear(t_trm *self)
{
	ft_ostream_puts(&self->out, tgoto(tgetstr("cm", NULL), 0, 0));
	ft_ostream_puts(&self->out, tgetstr("ce", NULL));
	ft_ostream_puts(&self->out, tgoto(tgetstr("cm", NULL), 0, 0));
	ft_ostream_puts(&self->out, tgetstr("cd", NULL));
	ft_ostream_puts(&self->out, tgoto(tgetstr("cm", NULL), 0, 0));
	ft_ostream_puts(&self->out, tgetstr("cl", NULL));
	ft_ostream_flush(&self->out);
}
