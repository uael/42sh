/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/read.c                                          :+:      :+:    :+:   */
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

static char			**g_renv;

static inline int	readparse(int ac, char *av[], t_readopt *ropt)
{
	int		opt;
	int64_t	time;

	g_optind = 1;
	while ((opt = ft_getopt(ac, av, "rst:n:u:p:d:")) != -1)
		if (opt == 'r')
			ropt->flags |= READ_R;
		else if (opt == 's')
			ropt->flags |= READ_S;
		else if (opt == 't' && (ropt->flags |= READ_T))
			if ((time = ft_atoi(g_optarg)))
				ropt->timeout = time;
			else
				ropt->timeout = -1;
		else if (opt == 'n' && (ropt->flags |= READ_L))
			ropt->nchars = (int)ft_atoi(g_optarg);
		else if (opt == 'u' && (ropt->flags |= READ_U))
			ropt->fd = (int)ft_atoi(g_optarg);
		else if (opt == 'p')
			ropt->prompt = g_optarg;
		else if (opt == 'd' && (ropt->flags |= READ_D))
			ropt->delim = *g_optarg;
		else
			return (WUT);
	return (g_optind);
}

inline static void	readarg(int ac, char **av, char *ln, int i)
{
	char *chr;
	char *ifs;

	if (!(ifs = ft_getenv(g_renv, "IFS")))
		ifs = " \t\n";
	while (*ln && i < ac)
	{
		if (!(chr = ft_strmchr(ln, ifs)))
		{
			sh_isident(av[i], ft_strlen(av[i])) ? sh_varset(av[i], ln) : 0;
			break ;
		}
		if (i + 1 < ac)
		{
			*chr++ = '\0';
			while (ft_strchr(ifs, *chr))
				++chr;
		}
		sh_isident(av[i], ft_strlen(av[i])) ? sh_varset(av[i++], ln) : 0;
		ln = chr;
	}
}

inline static int	readloop(t_sds *ln, t_readopt *ropt)
{
	int		i;
	int		esc;
	int		ret;
	char	buf[2];

	esc = 0;
	i = 0;
	if (ropt->prompt && (ropt->flags & READ_I))
		ft_puts(1, ropt->prompt);
	while (1)
	{
		if ((ret = (int)read(ropt->fd, buf, 1)) <= 0)
			return (ret);
		buf[ret] = 0;
		ft_putc(1, (char)(ropt->flags & READ_S ? 0 : *buf));
		if (!esc && *buf == ropt->delim)
			break ;
		esc = esc ? 0 : !(ropt->flags & READ_R) && (*buf == '\\');
		ft_sdsapd(ln, buf);
		if (*buf == '\n' && !(ropt->flags & (READ_R | READ_S | READ_I)))
			ft_puts(1, "> ");
		if ((ropt->flags & READ_L) && ++i >= ropt->nchars)
			break ;
	}
	return (0);
}

static void			optinit(t_readopt *ropt, char **env)
{
	ft_bzero(ropt, sizeof(t_readopt));
	ropt->delim = '\n';
	g_renv = env;
}

inline int			sh_biread(int ac, char **av, char **env)
{
	t_sds			ln;
	int				i;
	struct termios	term;
	int				st;
	t_readopt		opt;

	optinit(&opt, env);
	ft_sdsctor(&ln);
	if (!isatty(STDIN_FILENO) || (i = readparse(ac, av, &opt)) < 0 ||
		opt.timeout == -1)
		return (EXIT_FAILURE);
	opt.flags |= READ_I;
	if (tcgetattr(STDIN_FILENO, &term))
		return (ft_retf(EXIT_FAILURE, "read: %e\n", errno));
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VTIME] = (cc_t)(opt.timeout * 10);
	term.c_cc[VMIN] = (cc_t)(opt.timeout ? 0 : 1);
	term.c_cc[VEOL] = (cc_t)opt.delim;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term))
		return (ft_retf(EXIT_FAILURE, "read: %e\n", errno));
	if ((st = readloop(&ln, &opt)) || !ln.buf)
		return (ft_dtor(st ? st : EXIT_FAILURE, (t_dtor)ft_sdsdtor, &ln, NULL));
	ac == i ? sh_varset("REPLY", ln.buf) : readarg(ac, av, ln.buf, i);
	ft_sdsdtor(&ln);
	return (EXIT_SUCCESS);
}
