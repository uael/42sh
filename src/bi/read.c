/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:09:31 by cmalfroy          #+#    #+#             */
/*   Updated: 2018/02/12 15:09:34 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush.h"

#define READ_T 1 << 1
#define READ_U 1 << 2
#define READ_D 1 << 3
#define READ_R 1 << 4
#define READ_S 1 << 5
#define READ_I 1 << 6
#define READ_L 1 << 7

static ssize_t		g_timeout = 0;
static char			g_delim = '\n';
static int			g_fd = STDIN_FILENO;
static char			*g_prompt = NULL;
static uint8_t		g_flags = 0;
static int			g_nchars = 0;

static inline int	readparse(int ac, char *av[])
{
	int		opt;
	int64_t	time;

	g_optind = 1;
	while ((opt = ft_getopt(ac, av, "rst:n:u:p:d:")) != -1)
		if (opt == 'r')
			g_flags |= READ_R;
		else if (opt == 's')
			g_flags |= READ_S;
		else if (opt == 't' && (g_flags |= READ_T))
			if ((time = ft_atoi(g_optarg)))
				g_timeout = time;
			else
				g_timeout = -1;
		else if (opt == 'n' && (g_flags |= READ_L))
			g_nchars = (int)ft_atoi(g_optarg);
		else if (opt == 'u' && (g_flags |= READ_U))
			g_fd = (int)ft_atoi(g_optarg);
		else if (opt == 'p')
			g_prompt = g_optarg;
		else if (opt == 'd' && (g_flags |= READ_D))
			g_delim = *g_optarg;
		else
			return (WUT);
	return (g_optind);
}

inline static void	readarg(int ac, char **av, char *ln, int i)
{
	char	*chr;

	while (*ln && i < ac)
	{
		if (!(chr = ft_strmchr(ln, " \t\n")))
		{
			sh_isname(av[i]) ? sh_varset(av[i], ln) : 0;
			break ;
		}
		if (i + 1 < ac)
		{
			*chr++ = '\0';
			while (ft_strchr(" \t\n", *chr))
				++chr;
		}
		sh_isname(av[i]) ? sh_varset(av[i++], ln) : 0;
		ln = chr;
	}
}

inline static int	readloop(t_sds *ln)
{
	int		i;
	int		esc;
	int		ret;
	char	buf[2];

	esc = 0;
	i = 0;
	if (g_prompt && (g_flags & READ_I))
		ft_puts(1, g_prompt);
	while (1)
	{
		if ((ret = (int)read(g_fd, buf, 1)) <= 0)
			return (ret);
		buf[ret] = 0;
		ft_putc(1, (char)(g_flags & READ_S ? 0 : *buf));
		if (!esc && *buf == g_delim)
			break ;
		esc = esc ? 0 : !(g_flags & READ_R) && (*buf == '\\');
		ft_sdsapd(ln, buf);
		if (*buf == '\n' && !(g_flags & (READ_R | READ_S | READ_I)))
			ft_puts(1, "> ");
		if ((g_flags & READ_L) && ++i >= g_nchars)
			break ;
	}
	return (0);
}

inline int			sh_biread(int ac, char **av, char **env)
{
	t_sds			ln;
	int				i;
	struct termios	term;
	int				st;

	(void)env;
	ft_sdsctor(&ln);
	if (!isatty(STDIN_FILENO) || (i = readparse(ac, av)) < 0 || g_timeout == -1)
		return (EXIT_FAILURE);
	g_flags |= READ_I;
	if (tcgetattr(STDIN_FILENO, &term))
		return (ft_retf(EXIT_FAILURE, "read: %e\n", errno));
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VTIME] = (cc_t)(g_timeout * 10);
	term.c_cc[VMIN] = (cc_t)(g_timeout ? 0 : 1);
	term.c_cc[VEOL] = (cc_t)g_delim;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term))
		return (ft_retf(EXIT_FAILURE, "read: %e\n", errno));
	if ((st = readloop(&ln)) || !ln.buf)
		return (ft_dtor(st ? st : EXIT_FAILURE, (t_dtor)ft_sdsdtor, &ln, NULL));
	ac == i ? sh_varset("REPLY", ln.buf) : readarg(ac, av, ln.buf, i);
	ft_sdsdtor(&ln);
	return (YEP);
}
