/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:14 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:29:11 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdio.h>

#include "libft/term.h"

# define K_RETURN		"\xa"
# define K_BACKSPACE	"\x7f"
# define K_DELETE		"\x1b\x5b\x33\x7e"
# define K_CTRL_U		"\x15"
# define K_CTRL_D		"\x4"
# define K_CTRL_A		"\x1"
# define K_CTRL_E		"\x5"
# define K_CTRL_R		"\x12"
# define K_CTRL_L		"\xc"
# define K_CTRL_K		"\xb"
# define K_CTRL_P		"\x10"
# define K_ALT_B		"\x1b\x62"
# define K_ALT_F		"\x1b\x66"
# define K_UP			"\x1b\x5b\x41"
# define K_DOWN			"\x1b\x5b\x42"
# define K_RIGHT		"\x1b\x5b\x43"
# define K_LEFT			"\x1b\x5b\x44"
# define K_SHIFT_UP "\x1b\x5b\x31\x3b\x32\x41"
# define K_SHIFT_DOWN "\x1b\x5b\x31\x3b\x32\x42"
# define K_SHIFT_RIGHT "\x1b\x5b\x31\x3b\x32\x43"
# define K_SHIFT_LEFT "\x1b\x5b\x31\x3b\x32\x44"

# define K_HOME		"\x1b\x5b\x48"
# define K_END			"\x1b\x5b\x46"
# define K_CTRL_Y		"\x19"

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
#define TC_DON 18
#define TC_UPN 19

static int		g_tty = 0;
char			*g_tcaps[TC_UPN + 1] = {NULL};
static char		*g_tnames[TC_UPN + 1] =
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
		[TC_DON] = "DO",
		[TC_UPN] = "UP",
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

static void		term_refresh_size(t_term *self)
{
	struct winsize	w;

	ioctl(self->fd, TIOCGWINSZ, &w);
	self->col = w.ws_col;
	self->row = w.ws_row;
}

static int		term_cursor(int tty, uint32_t *col, uint32_t *row)
{
	uint8_t	c;
	int		st;

	if (ft_write(tty, "\033[6n", 4) < 0)
		return (WUT);
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

static int		term_left(t_term *self)
{
	if (!self->curs.i)
		return (YEP);
	if (tputs(caps(TC_LE), 1, tputs_c))
		return (THROW(WUT));
	--self->curs.i;
	if (self->curs.x == 0)
	{
		if (tputs(caps(TC_UP), 1, tputs_c))
			return (THROW(WUT));
		if (tputs(tgoto(caps(TC_CH), 0, (int)(self->col - 1)), 1, tputs_c))
			return (THROW(WUT));
		self->curs.x = (uint32_t)self->col;
	}
	--self->curs.x;
	return (YEP);
}

static int		term_right(t_term *self)
{
	if ((size_t)self->curs.i >= self->line.len)
		return (YEP);
	if (tputs(caps(TC_ND), 1, tputs_c))
		return (THROW(WUT));
	++self->curs.i;
	if ((++self->curs.x % self->col) == 0)
	{
		if (tputs(caps(TC_DO), 1, tputs_c))
			return (THROW(WUT));
		if (tputs(tgoto(caps(TC_CH), 0, 0), 1, tputs_c))
			return (THROW(WUT));
		self->curs.x = 0;
	}
	return (YEP);
}

static int		term_delc(t_term *self)
{
	if (!self->line.len)
		return (YEP);
	if (tputs(caps(TC_DC), 1, tputs_c))
		return (THROW(WUT));
	if (self->curs.x == self->col - 1)
	{
		tputs(" ", 1, tputs_c);
		tputs(caps(TC_LE), 1, tputs_c);
		tputs(caps(TC_ND), 1, tputs_c);
	}
	ft_dstr_remove(&self->line, (size_t)self->curs.i, NULL);
	return (YEP);
}

static int		term_putc(t_term *self, char c, size_t pl)
{
	char	*s;
	int		n;

	if (self->mode != TERM_INSERT)
		return (YEP);
	n = (int)((self->line.len - self->curs.i + pl) / self->col) + 1;
	if (tputs(caps(TC_IC), 3, tputs_c))
		return (THROW(WUT));
	s = alloca(2 * sizeof(char));
	s[0] = c;
	s[1] = '\0';
	if (tputs(s, n, tputs_c) || tputs(caps(TC_IP), n, tputs_c))
		return (THROW(WUT));
	ft_dstr_putc(&self->line, self->curs.i, c);
	++self->curs.i;
	if ((++self->curs.x % self->col) == 0)
	{
		if (tputs(caps(TC_DO), 1, tputs_c))
			return (THROW(WUT));
		if (tputs(tgoto(caps(TC_CH), 0, 0), 1, tputs_c))
			return (THROW(WUT));
		self->curs.x = 0;
	}
	return (YEP);
}

static int		term_puts(t_term *self, char const *s, size_t pl)
{
	int st;

	while (*s)
		if ((st = term_putc(self, *s++, pl)))
			return (st);
	return (YEP);
}

static int		term_putnl(t_term *self, char const *s, size_t pl)
{
	int st;

	while (*s && *s != '\n')
		if ((st = term_putc(self, *s++, pl)))
			return (st);
	return (YEP);
}

static int		term_clrl(t_term *self, char *prompt)
{
	size_t pl;
	int		n;

	if (self->line.len)
	{
		ft_memset(self->line.buf, 0, self->line.len);
		self->line.len = 0;
	}
	pl = ft_strlen(prompt);
	if (self->curs.x)
	{
		if (tputs(tgoto(caps(TC_CH), 0, 0), 1, tputs_c))
			return (THROW(WUT));
		if (tputs(caps(TC_CE), 1, tputs_c))
			return (THROW(WUT));
		self->curs.x = 0;
	}
	if (self->curs.i)
	{
		if ((n = (int)((self->curs.i + pl) / self->col)))
		{
			while (n--)
			{
				if (tputs(tgoto(caps(TC_UP), 1, 1), 1, tputs_c))
					return (THROW(WUT));
				if (tputs(caps(TC_CE), n, tputs_c))
					return (THROW(WUT));
			}
		}
		self->curs.i = 0;
	}
	if (tputs(prompt, 1, tputs_c))
		return (THROW(WUT));
	self->curs.x += pl;
	return (YEP);
}

static char		*rl_exit(t_term *self, char *ret)
{
	self->curs.i = 0;
	if (self->mode == TERM_INSERT)
	{
		if (tputs(caps(TC_EI), 1, tputs_c))
		{
			THROW(WUT);
			ret = NULL;
		}
		tcsetattr(self->fd, TCSANOW, &self->off);
		self->mode = TERM_OFF;
	}
	return (ret);
}

inline char		*ft_readline(t_term *self, char *prompt)
{
	int		r;
	char	buf[7];
	size_t	pl;

	if (self->mode == TERM_NOTTY)
		return (ft_istream_getl(g_cin, '\n'));
	else
	{
		pl = ft_strlen(prompt);
		if (self->mode == TERM_OFF)
		{
			tcsetattr(self->fd, TCSADRAIN, &self->on);
			term_refresh_size(self);
			if (term_cursor(self->fd, &self->curs.x, &self->curs.y) ||
				tputs(caps(TC_IM), 1, tputs_c))
			{
				THROW(WUT);
				return (rl_exit(self, NULL));
			}
			self->mode = TERM_INSERT;
		}
		if (term_clrl(self, prompt))
			return (rl_exit(self, NULL));
		while (ft_memset(buf, 0, 7) && (r = (int)read(self->fd, buf, 6)))
		{
			if (r < 0 && (errno == EAGAIN || errno == EINTR))
				continue ;
			if (r < 0)
			{
				THROW(WUT);
				return (rl_exit(self, NULL));
			}
			if (r == 3 && ft_strcmp(K_UP, buf) == 0)
			{
				if (self->hcurs)
					--self->hcurs;
				if (self->hcurs < ft_vstr_size(&self->history))
				{
					if (term_clrl(self, prompt) ||
						term_putnl(self, *ft_vstr_at(&self->history, self->hcurs), pl))
						return (rl_exit(self, NULL));
				}
			}
			else if (r == 3 && ft_strcmp(K_DOWN, buf) == 0)
			{
				if (self->hcurs < ft_vstr_size(&self->history))
					++self->hcurs;
				if (term_clrl(self, prompt))
					return (rl_exit(self, NULL));
				if (self->hcurs < ft_vstr_size(&self->history) &&
					term_putnl(self, *ft_vstr_at(&self->history, self->hcurs), pl))
					return (rl_exit(self, NULL));
			}
			else if (r == 3 && ft_strcmp(K_LEFT, buf) == 0)
			{
				if (term_left(self))
					return (rl_exit(self, NULL));
			}
			else if (r == 6 && ft_strcmp(K_SHIFT_LEFT, buf) == 0)
			{
				if (self->line.len)
				{
					if (self->curs.i && term_left(self))
						return (rl_exit(self, NULL));
					while (self->curs.i &&
						ft_strchr(" \t",
						*ft_dstr_at(&self->line, self->curs.i)))
					{
						if (term_left(self))
							return (rl_exit(self, NULL));
					}
					while (self->curs.i)
					{
						if (ft_strchr(" \t",
							*(ft_dstr_at(&self->line, self->curs.i) - 1)))
							break ;
						if (term_left(self))
							return (rl_exit(self, NULL));
					}
				}
			}
			else if (r == 3 && ft_strcmp(K_RIGHT, buf) == 0)
			{
				if (term_right(self))
					return (rl_exit(self, NULL));
			}
			else if (r == 6 && ft_strcmp(K_SHIFT_RIGHT, buf) == 0)
			{
				if (self->line.len)
				{
					while (self->curs.i < self->line.len &&
						!ft_strchr(" \t",
						*ft_dstr_at(&self->line, self->curs.i)))
					{
						if (term_right(self))
							return (rl_exit(self, NULL));
					}
					while (self->curs.i < self->line.len &&
						ft_strchr(" \t",
						*ft_dstr_at(&self->line, self->curs.i)))
					{
						if (term_right(self))
							return (rl_exit(self, NULL));
					}
					if (self->curs.i == self->line.len)
					{
						while (self->curs.i &&
							ft_strchr(" \t",
							*ft_dstr_at(&self->line, self->curs.i)))
						{
							if (term_left(self))
								return (rl_exit(self, NULL));
						}
						while (self->curs.i)
						{
							if (ft_strchr(" \t",
								*(ft_dstr_at(&self->line, self->curs.i) - 1)))
								break ;
							if (term_left(self))
								return (rl_exit(self, NULL));
						}
					}
				}
			}
			else if (ft_strcmp(K_HOME, buf) == 0)
			{
				if (self->line.len)
				{
					while (self->curs.i)
						if (term_left(self))
							return (rl_exit(self, NULL));
				}
			}
			else if (ft_strcmp(K_END, buf) == 0)
			{
				if (self->line.len)
				{
					while (self->curs.i < self->line.len)
						if (term_right(self))
							return (rl_exit(self, NULL));
				}
			}
			else if (r == 4 && ft_strcmp(K_DELETE, buf) == 0)
			{
				if (term_delc(self))
					return (rl_exit(self, NULL));
			}
			else if (r == 1 && ft_strcmp(K_BACKSPACE, buf) == 0)
			{
				if (term_left(self) || term_delc(self))
					return (rl_exit(self, NULL));
			}
			else if (r == 1 && ft_strcmp(K_RETURN, buf) == 0)
			{
				while (self->curs.i < self->line.len)
					term_right(self);
				if (term_puts(self, "\n", pl))
					return (rl_exit(self, NULL));
				break ;
			}
			else if (r > 1 || (*buf < 32 || *buf == 127) || !ft_isascii(*buf))
			{
				char *s = buf;

				dprintf(2, "\"");
				while (*s)
					dprintf(2, "\\x%x", *s++);
				dprintf(2, "\"\n");
			}
			else
			{
				if (term_putc(self, *buf, pl))
					return (rl_exit(self, NULL));
			}
		}
		if (self->line.len && (!ft_vstr_size(&self->history) ||
			ft_strcmp(*(ft_vstr_end(&self->history) - 1), self->line.buf)))
		{
			ft_vstr_pushc(&self->history, ft_strdup(self->line.buf));
			while (ft_vstr_size(&self->history) > 100)
				ft_vstr_shift(&self->history, NULL);
		}
		self->hcurs = ft_vstr_size(&self->history);
		return (rl_exit(self, self->line.buf));
	}
}
