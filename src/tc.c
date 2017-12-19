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
#define TC_DC 9
#define TC_IC 10
#define TC_IM 11
#define TC_EI 12
#define TC_RC 13
#define TC_SC 14
#define TC_IP 15
#define TC_DM 16
#define TC_ED 17

static int		g_tty = 0;
char			*g_tcaps[TC_ED + 1] = {NULL};
static char		*g_tnames[TC_ED + 1] =
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
	[TC_DC] = "dc",
	[TC_IC] = "ic",
	[TC_IM] = "im",
	[TC_EI] = "ei",
	[TC_RC] = "rc",
	[TC_SC] = "ic",
	[TC_IP] = "ip",
	[TC_DM] = "dm",
	[TC_ED] = "ed",
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

static void		s_tc_refresh(t_tc *self)
{
	struct winsize	w;

	ioctl(self->tty, TIOCGWINSZ, &w);
	self->col = w.ws_col;
	self->row = w.ws_row;
}

int g_log = 0;

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

inline int		tc_ctor(t_tc *self, char **env, void *arg)
{
	char		*term;

	FT_INIT(self, t_tc);
	if (!(term = ft_getenv(env, "TERM")))
		term = "xterm";
	if (!(self->ttyn = ttyname(STDIN_FILENO)) &&
		!(self->ttyn = ttyname(STDOUT_FILENO)) &&
		!(self->ttyn = ttyname(STDERR_FILENO)))
		return (ENO_THROW(WUT, ENOTTY));
	if (tgetent(NULL, term) <= 0 ||
		(self->tty = open(self->ttyn, O_RDWR, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(WUT));
	self->arg = arg;
	tcgetattr(self->tty, &self->curr);
	ft_memcpy(&self->prev, &self->curr, sizeof(t_tcios));
	self->curr.c_lflag &= ~(ICANON | ECHO);
	self->curr.c_cc[VMIN] = 1;
	self->curr.c_cc[VTIME] = 10;
	g_tty = self->tty;
	tc_switch(self, TC_INSERT);
	return (YEP);
}

inline void		tc_dtor(t_tc *self)
{
	tc_switch(self, TC_NONE);
	ft_du8_dtor(&self->r, NULL);
	tc_pause(self);
	if (close(self->tty))
		THROW(WUT);
}

inline int 		tc_switch(t_tc *self, t_tc_m mode)
{
	if (self->mode == mode)
		return (YEP);
	if (mode == TC_INSERT)
	{
		if (tputs(caps(TC_IM), 1, tputs_c))
			return (THROW(WUT));
	}
	else if (tputs(caps(TC_EI), 1, tputs_c))
		return (THROW(WUT));
	self->mode = mode;
	return (YEP);
}

inline void		tc_pause(t_tc *self)
{
	tc_switch(self, TC_NONE);
	tcsetattr(self->tty, TCSADRAIN, &self->prev);
}

inline int		tc_resume(t_tc *self)
{
	tcsetattr(self->tty, TCSADRAIN, &self->curr);
	s_tc_refresh(self);
	tc_switch(self, TC_INSERT);
	trm_cursor(self->tty, &self->x, &self->y);
	return (YEP);
}

extern int		tc_delc(t_tc *self)
{
	if (!self->in.len)
		return (YEP);
	if (tputs(caps(TC_DC), 1, tputs_c))
		return (THROW(WUT));
	if (self->x == self->col - 1)
	{
		tputs(" ", 1, tputs_c);
		tputs(caps(TC_LE), 1, tputs_c);
		tputs(caps(TC_ND), 1, tputs_c);
	}
	ft_dstr_remove(&self->in, (size_t)self->c, NULL);
	return (YEP);
}

inline int		tc_putc(t_tc *self, char c)
{
	char	*s;

	if (self->mode != TC_INSERT)
		return (YEP);
	if (tputs(caps(TC_IC), 1, tputs_c))
		return (THROW(WUT));
	s = alloca(2 * sizeof(char));
	s[0] = c;
	s[1] = '\0';
	if (tputs(s, 1, tputs_c) || tputs(caps(TC_IP), 1, tputs_c))
		return (THROW(WUT));
	ft_dstr_putc(&self->in, (size_t)self->c, c);
	++self->c;
	if ((++self->x % self->col) == 0)
	{
		if (tputs(caps(TC_DO), 1, tputs_c))
			return (THROW(WUT));
		if (tputs(tgoto(caps(TC_CH), 0, 0), 1, tputs_c))
			return (THROW(WUT));
		self->x = 0;
	}
	return (YEP);
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

inline int		tc_clrln(t_tc *self)
{
	self->c = 0;
	if (tputs(caps(TC_CE), 1, tputs_c))
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
	/*if (tputs(tgoto(caps(TC_CH), 0, 0), 1, tputs_c))
		return (THROW(WUT));*/
	return (YEP);
}

inline int		tc_left(t_tc *self)
{
	if (!self->c)
		return (YEP);
	if (tputs(caps(TC_LE), 1, tputs_c))
		return (THROW(WUT));
	--self->c;
	if (self->x == 0)
	{
		if (tputs(caps(TC_UP), 1, tputs_c))
			return (THROW(WUT));
		if (tputs(tgoto(caps(TC_CH), 0, self->col - 1), 1, tputs_c))
			return (THROW(WUT));
		self->x = self->col;
	}
	--self->x;
	return (YEP);
}

inline int		tc_right(t_tc *self)
{
	if ((size_t)self->c >= self->in.len)
		return (YEP);
	if (tputs(caps(TC_ND), 1, tputs_c))
		return (THROW(WUT));
	++self->c;
	if ((++self->x % self->col) == 0)
	{
		if (tputs(caps(TC_DO), 1, tputs_c))
			return (THROW(WUT));
		if (tputs(tgoto(caps(TC_CH), 0, 0), 1, tputs_c))
			return (THROW(WUT));
		self->x = 0;
	}
	return (YEP);
}

inline int		tc_up(t_tc *self)
{
	(void)self;
	return (YEP);
}

inline int		tc_down(t_tc *self)
{
	(void)self;
	return (YEP);
}

inline int		tc_loop(t_tc *self, t_tc_hook hook)
{
	int		st;
	int		r;
	char	buf[7];

	tc_resume(self);
	if (!g_log)
		g_log = open("/Users/alucas-/.21shlog", O_APPEND | O_CREAT | O_RDWR,
			S_IRUSR | S_IWUSR);
	st = 0;
	r = 0;
	while (ft_memset(buf, 0, 7) && (r = (int)read(self->tty, buf, 6)) > 0)
	{
		if ((st = hook(self, buf)))
			break;
		dprintf(g_log, "[%d:%d] <%d:%d> <%d>\n", self->col, self->row,
			self->x, self->y, self->c);
		dprintf(g_log, "in[%zu]: '%s'\n", self->in.len, self->in.buf);
	}
	return (r < 0 ? WUT : st);
}
