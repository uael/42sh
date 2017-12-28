/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>

#ifndef TTY
# define TTY struct termios
#endif

#define HIST_MAX (100)
#define LN_MAX (2048)

typedef struct s_ln
{
	char const	*prompt;
	size_t		polen;
	char		**parts;
	char		*resolved;
	uint16_t	len;
	uint16_t	idx;
	uint16_t	pidx;
	uint16_t	plen;
	uint16_t	pcap;
	struct s_ln	*orig;
}				t_ln;

typedef int		(t_rlbind)(t_ln *line);

typedef enum	e_mode
{
	RL_NONE,
	RL_OFF,
	RL_INSERT,
	RL_SEARCH,
	RL_VISUAL
}				t_mode;

static t_ln		g_hist[HIST_MAX] = { 0 };
static uint8_t	g_hist_len = 0;
static uint8_t	g_hist_idx = 0;
static t_mode	g_mode = RL_NONE;
static TTY		g_orig_mode;
static TTY		g_raw_mode;
static uint16_t g_cols = 0;
static uint16_t g_pos = 0;
static struct s_rlbind
{
	uint8_t		klen;
	char const	*key;
	t_rlbind	bind;
}				g_binds[UINT8_MAX] = { 0 };

static int	rl_cursor(int ifd, int ofd)
{
	char	buf[32];
	uint	i;

	i = 0;
	if (ft_write(ofd, "\x1b[6n", 4) != 4)
		return (THROW(WUT));
	while (++i < sizeof(buf))
		if (ft_read(ifd, buf + i - 1, 1) != 1 || buf[i] == 'R')
			break;
	buf[i] = '\0';
	if (buf[0] != 27 || buf[1] != '[')
		return (WUT);
	return ((int)ft_atoi(ft_strchr(buf, ';') + 1));
}

static int		rl_cols(int ifd, int ofd)
{
	struct winsize	ws;
	int				start;
	int				cols;
	char			seq[32];

	if (ioctl(1, TIOCGWINSZ, &ws) != -1 && ws.ws_col != 0)
		return (ws.ws_col);
	else
	{
		if ((start = rl_cursor(ifd, ofd)) == -1)
			return (WUT);
		if (ft_write(ofd, "\x1b[999C", 6) != 6)
			return (THROW(WUT));
		if ((cols = rl_cursor(ifd, ofd)) == -1)
			return (WUT);
		if (cols > start)
		{
			ft_memcpy(seq, "\x1b[", sizeof("\x1b["));
			seq[ft_intstr(seq + sizeof("\x1b["), cols - start, 10)] = '\0';
			if (ft_write(ofd, ft_strcat(seq, "D"), ft_strlen(seq)) < 0)
				return ((int16_t)THROW(WUT));
		}
		return (cols);
	}
}

static char		*rl_notty(int fd)
{
	static t_ifs	in[OPEN_MAX + 1] = { 0 };
	static ssize_t	rd[OPEN_MAX + 1] = { 0 };
	char			*ln;
	
	if (fd <= 0 || fd > OPEN_MAX)
	{
		ENO_THROW(WUT, EINVAL);
		return (NULL);
	}
	if (rd[fd] > 0 && ft_ifsrd(in + fd, NULL, (size_t)rd[fd]) < 0)
		return (NULL);
	if ((rd[fd] = ft_ifschr(in + fd, 0, '\n', &ln)) > 0)
		return (ln);
	return (NULL);
}

t_ln			*ln_clear(t_ln *self)
{
	uint16_t	i;

	i = 0;
	while (i < self->plen)
		*self->parts[i++] = '\0';
	*self->resolved = '\0';
	self->prompt = NULL;
	self->polen = 0;
	self->len = 0;
	self->idx = 0;
	self->plen = 0;
	self->pidx = 0;
	return (self);
}

void			ln_push(void)
{
	t_ln		tmp;

	g_hist_idx = 0;
	if (!g_hist[g_hist_len ? g_hist_len - 1 : 0].len)
		return ;
	if (g_hist_len != HIST_MAX)
		++g_hist_len;
	else
	{
		tmp = g_hist[0];
		ft_memmove(g_hist, g_hist + 1, (HIST_MAX - 1) * sizeof(t_ln));
		g_hist[HIST_MAX - 1] = tmp;
		ln_clear(g_hist + HIST_MAX - 1);
	}
}

inline t_ln		*ln(void)
{
	return (g_hist + (g_hist_len ? g_hist_len - 1 : 0) - g_hist_idx);
}

int				rl_edit(void)
{
	ssize_t			rd;
	char			key[6];
	struct s_rlbind	*b;
	int				st;

	while ((rd = ft_read(STDIN_FILENO, key, 6)) > 0)
	{
		b = g_binds - 1;
		st = 1;
		while ((++b)->key)
			if (rd == b->klen && !ft_memcmp(b->key, key, (size_t)rd))
			{
				if (!b->bind || (st = b->bind(ln())) == 0)
					break ;
				return (st < 0 ? WUT : YEP);
			}
		if (st && rd == 1 && !ft_iscntrl(*key) && ft_isascii(*key))
			rl_insert(*key);
		else if (st)
		{
			char *s = key;

			dprintf(2, "\"");
			while (*s && rd--)
				dprintf(2, "\\x%x", *s++);
			dprintf(2, "\"\n");
		}
	}
	return (YEP);
}

char			*rl_exit(char *result, int eno)
{
	if (eno)
		ENO_THROW(WUT, eno);
	if (g_mode != RL_OFF)
	{
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &g_orig_mode) < 0)
			return (NULL);
		g_mode = RL_OFF;
	}
	return (result);
}

char			*sh_readline(int fd, char const *prompt)
{
	int				cols;

	if (fd != 0 || !isatty(fd))
		return (rl_notty(fd));
	if (g_mode == RL_NONE)
	{
		if (tcgetattr(fd, &g_orig_mode) == -1)
			return (rl_exit(NULL, ENOTTY));
		g_raw_mode = g_orig_mode;
		g_raw_mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | OPOST);
		g_raw_mode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		g_raw_mode.c_cflag |= (CS8);
		g_raw_mode.c_cc[VMIN] = 1;
		g_raw_mode.c_cc[VTIME] = 0;
		g_mode = RL_OFF;
	}
	ln_push();
	if (ft_write(STDOUT_FILENO, ln()->prompt = prompt,
		ln()->polen = ft_strlen(prompt)) < 0)
		return (rl_exit(NULL, 0));
	if (g_mode != RL_INSERT)
	{
		if (tcsetattr(fd, TCSADRAIN, &g_raw_mode) < 0)
			return (rl_exit(NULL, ENOTTY));
		g_mode = RL_INSERT;
	}
	if ((cols = rl_cols(fd, STDOUT_FILENO)) <= 0)
		return (rl_exit(NULL, 0));
	g_cols = (uint16_t)cols;
	if (rl_edit())
		return (rl_exit(NULL, 0));
	return (rl_exit(ln()->len ? ln()->resolved : NULL, 0));
}
