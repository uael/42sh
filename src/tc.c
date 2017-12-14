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
#include "msh/tc.h"

#define TC_U7 0
#define TC_DO 1
#define TC_CH 2
#define TC_CM 3
#define TC_UP 4
#define TC_LE 5
#define TC_ND 6

static int		g_tty = 0;
static int		g_log = 0;
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
	g_log = open("/Users/alucas-/.21shlog", O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
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

inline int		tc_putc(t_tc *self, char c)
{
	char *s;

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
	ft_dstr_pushc(&self->in, c);
	if (c == '\n')
		return (YEP);
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
	int st;

	st = tputs(tgoto(caps(TC_CM), self->sx, self->sy), 0, tputs_c);
	self->x = self->sx;
	self->y = self->sy;
	return (st);
}

inline int		tc_clr(t_tc *self)
{
	(void)self;
	return (ENO_THROW(WUT, ENIMPL));
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
	else if (self->x)
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

inline void		tc_hook(t_tc *self, int ch, t_tc_hook hook)
{
	self->hook[ch] = hook;
}

#define TRK_ONEK(ch) ((ch)==9||(ch)==10||(ch)==32||(ch)==127||(ch)==27)

static int		tc_getch(t_tc *t)
{
	uint8_t	c[2];
	uint8_t	n;
	int		r;

	n = 0;
	ft_memset(c, 0, 2 * sizeof(char));
	while (42)
		if (!ft_du8_size(&t->r) &&
			((r = (int)read(t->tty, &c, 2)) < 0 ||
			 (r > 0 && !ft_du8_pushnc(&t->r, c, (size_t)r))))
			return (THROW(WUT));
		else if (ft_du8_shiftn(&t->r, 2, c) <= 0)
			break ;
		else if ((n += r) == 1 && TRK_ONEK(c[0]))
			return (c[0]);
		else if (n == 2 && c[0] == 27 && c[1] == 91)
			continue ;
		else if (n == 4 && c[0] == 51 && c[1] == 126)
			return (c[1]);
		else if (n == 3 && (c[0] >= 65 && c[0] <= 68))
			return (c[0]);
		else if (n >= 1)
		{
			if (n <= t->r.cur)
				t->r.cur -= n;
			if (ft_du8_shiftn(&t->r, 1, c))
				return (*c);
			break ;
		}
	return (0);
}

inline int		tc_loop(t_tc *self)
{
	int ch;
	int st;

	tc_resume(self);
	trm_cursor(self->tty, &self->sx, &self->sy);
	self->x = self->sx;
	self->y = self->sy;
	st = 0;
	ft_putf(g_log, "[%d|%d] <%d,%d> <%d,%d>\n",
		self->col, self->row, self->sx, self->sy, self->x, self->y);
	while ((ch = tc_getch(self)) >= 0)
	{
		if (ch == TRK_DOWN)
			tc_down(self);
		else if (ch == TRK_UP)
			tc_up(self);
		else if (ch == TRK_LEFT)
			tc_left(self);
		else if (ch == TRK_RIGHT)
			tc_right(self);
		else if (self->hook[ch] && (st = self->hook[ch](self, ch)))
			break;
		else if (ch == TRK_ESC)
			break;
		else if (ch)
			tc_putc(self, (char)ch);
		ft_putf(g_log, "[%d|%d] <%d,%d> <%d,%d>\n",
			self->col, self->row, self->sx, self->sy, self->x, self->y);
	}
	tc_dtor(self);
	return (ch < 0 ? ch : st);
}
