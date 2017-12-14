/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdio.h>
#include "msh/tc.h"

#define TC_U7 0
#define TC_DO 1
#define TC_CH 2
#define TC_CM 3
#define TC_UP 4
#define TC_LE 5
#define TC_ND 6
#define TC_CD 7
#define TC_CE 8

static int		g_tty = 0;
char			*g_tcaps[10] = {NULL};
static char		*g_tnames[10] =
{
	[TC_U7] = "u7",
	[TC_DO] = "do",
	[TC_CH] = "ch",
	[TC_CM] = "cm",
	[TC_UP] = "up",
	[TC_LE] = "le",
	[TC_ND] = "nd",
	[TC_CD] = "cd",
	[TC_CE] = "ce",
};

static int		tputs_c(int c)
{
	return ((int)write(g_tty, &c, 1));
}

static char 	*caps(int kind)
{
	if (!g_tcaps[kind] && !(g_tcaps[kind] = tgetstr(g_tnames[kind], NULL)))
		g_tcaps[kind] = "";
	return (g_tcaps[kind]);
}

static int	trm_cursor(int tty, int *col, int *row)
{
	uint8_t	c;
	int		st;

	if (tty == -1)
		return ENOTTY;
	write(tty, "\033[6n", 4);
	st = EIO;
	if (read(tty, &c, 1) <= 0 || c != 27 || read(tty, &c, 1) <= 0 || c != '[')
		return (st);
	*row = 0;
	while (read(tty, &c, 1) > 0 && c >= '0' && c <= '9')
		*row = 10 * *row + c - '0';
	*row ? --*row : 0;
	if (c != ';')
		return (st);
	*col = 0;
	while (read(tty, &c, 1) > 0 && c >= '0' && c <= '9')
		*col = 10 * *col + c - '0';
	*col ? --*col : 0;
	if (c != 'R')
		return (st);
	return (0);
}

static void		s_tc_refresh(t_tc *self)
{
	struct winsize	w;

	if (!isatty(self->tty))
		return ;
	if (ioctl(self->tty, TIOCGWINSZ, &w))
		ft_fatal(NOP, (t_dtor)ft_trm_dtor, self, "ioctl: %e", errno);
	self->col = w.ws_col;
	self->row = w.ws_row;
}

inline int		tc_ctor(t_tc *self, char **env, void *arg)
{
	char		*term;
	char const	*tty;

	FT_INIT(self, t_tc);
	if (!(term = ft_getenv(env, "TERM")))
		return (ENO_THROW(WUT, ENOTRM));
	if (!(tty = ttyname(STDIN_FILENO)) &&
		!(tty = ttyname(STDOUT_FILENO)) &&
		!(tty = ttyname(STDERR_FILENO)))
		return (ENO_THROW(WUT, ENOTTY));
	if (tgetent(NULL, term) <= 0 ||
		(self->tty = open(tty, O_RDWR, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(WUT));
	self->arg = arg;
	tcgetattr(self->tty, &self->curr);
	ft_memcpy(&self->prev, &self->curr, sizeof(t_tcios));
	self->curr.c_lflag &= ~(ICANON | ECHO);
	self->curr.c_cc[VMIN] = 1;
	self->curr.c_cc[VTIME] = 0;
	g_tty = self->tty;
	return (YEP);
}

inline void		tc_dtor(t_tc *self)
{
	ft_du8_dtor(&self->r, NULL);
	tc_pause(self);
	if (close(self->tty))
		THROW(WUT);
}

inline void		tc_pause(t_tc *self)
{
	tcsetattr(self->tty, TCSADRAIN, &self->prev);
}

inline void		tc_resume(t_tc *self)
{
	tcsetattr(self->tty, TCSADRAIN, &self->curr);
	s_tc_refresh(self);
}

inline int		tc_register(t_tc *self)
{
	trm_cursor(self->tty, &self->sx, &self->sy);
	self->x = self->sx;
	self->y = self->sy;
	return (YEP);
}

inline int		tc_putc(t_tc *self, char c)
{
	char *s;

	ft_dstr_pushc(&self->in, c);
	if (c == '\n')
	{
		tc_down(self);
		tputs(tgoto(caps(TC_CH), 0, 0), 0, tputs_c);
		tc_register(self);
		return (YEP);
	}
	s_tc_refresh(self);
	if (((self->x + 1) % self->col) == 0)
	{
		if (tputs(caps(TC_DO), 0, tputs_c) ||
			tputs(tgoto(caps(TC_CH), 0, 0), 0, tputs_c))
			return (THROW(WUT));
		((self->y + 1) % self->row) == 0 ? --self->sy : ++self->y;
		self->x = 0;
	}
	++self->x;
	s = alloca(2 * sizeof(char));
	s[0] = c;
	s[1] = '\0';
	return (tputs(s, 0, tputs_c) ? THROW(WUT) : YEP);
}

inline int		tc_puts(t_tc *self, char const *s)
{
	int st;

	while (*s)
		if ((st = tc_putc(self, *s++)))
			return (st);
	return (YEP);
}

inline int		tc_putnl(t_tc *self, char const *s)
{
	int st;

	while (*s && *s != '\n')
		if ((st = tc_putc(self, *s++)))
			return (st);
	return (YEP);
}

inline int		tc_insc(t_tc *self, char c)
{
	(void)self;
	(void)c;
	return (ENO_THROW(WUT, ENIMPL));
}

inline int		tc_inss(t_tc *self, char const *s)
{
	(void)self;
	(void)s;
	return (ENO_THROW(WUT, ENIMPL));
}

inline int		tc_clrln(t_tc *self)
{
	if (self->sy + 1 < self->row)
	{
		if (tputs(tgoto(caps(TC_CM), 0, self->sy + 1), 0, tputs_c))
			return (THROW(WUT));
		if (tputs(caps(TC_CD), 0, tputs_c))
			return (THROW(WUT));
	}
	if (tputs(tgoto(caps(TC_CM), self->sx, self->sy), 0, tputs_c))
		return (THROW(WUT));
	self->x = self->sx;
	self->y = self->sy;
	if (tputs(caps(TC_CE), 0, tputs_c))
		return (THROW(WUT));
	ft_memset(self->in.buf, 0, self->in.len);
	self->in.len = 0;
	return (YEP);
}

inline int		tc_clr(t_tc *self)
{
	(void)self;
	return (ENO_THROW(WUT, ENIMPL));
}

inline int		tc_margin_left(t_tc *self)
{
	(void)self;
	if (tputs(tgoto(caps(TC_CH), 0, 0), 0, tputs_c))
		return (THROW(WUT));
	return (YEP);
}

inline int		tc_left(t_tc *self)
{
	if (!self->x && self->y > self->sy)
	{
		if (tputs(caps(TC_UP), 0, tputs_c) ||
			tputs(tgoto(caps(TC_CH), self->col - 1, self->col - 1), 0, tputs_c))
			return (THROW(WUT));
		self->x = self->col - 1;
		--self->y;
	}
	else if (self->x && (self->sy != self->y || self->x > self->sx))
	{
		if (tputs(caps(TC_LE), 0, tputs_c))
			return (THROW(WUT));
		--self->x;
	}
	return (YEP);
}

inline int		tc_right(t_tc *self)
{
	if ((++self->x % self->col) == 0)
	{
		if (tputs(caps(TC_DO), 0, tputs_c) ||
			tputs(tgoto(caps(TC_CH), 0, 0), 0, tputs_c))
			return (THROW(WUT));
		((self->y + 1) % self->row) == 0 ? --self->sy : ++self->y;
		self->x = 0;
	}
	else if (tputs(caps(TC_ND), 0, tputs_c))
		return (THROW(WUT));
	return (YEP);
}

inline int		tc_up(t_tc *self)
{
	if (self->y > self->sy)
	{
		if (tputs(caps(TC_UP), 0, tputs_c))
			return (THROW(WUT));
		--self->y;
		if (tputs(tgoto(caps(TC_CH), self->x, self->x), 0, tputs_c))
			return (THROW(WUT));
	}
	return (YEP);
}

inline int		tc_down(t_tc *self)
{
	if (tputs(caps(TC_DO), 0, tputs_c))
		return (THROW(WUT));
	((self->y + 1) % self->row) == 0 ? --self->sy : ++self->y;
	if (tputs(tgoto(caps(TC_CH), self->x, self->x), 0, tputs_c))
		return (THROW(WUT));
	return (YEP);
}

inline int		tc_loop(t_tc *self, t_tc_hook hook)
{
	int		st;
	int		r;
	char	buf[7];

	tc_resume(self);
	tc_register(self);
	st = 0;
	while (ft_memset(buf, 0, 7) && (r = (int)read(self->tty, buf, 6)) > 0)
		if ((st = hook(self, buf)))
			break;
	return (r < 0 ? WUT : st);
}
