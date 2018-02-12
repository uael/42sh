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

enum				e_readopt
{
	READ_T = 1 << 1,
	READ_U = 1 << 2,
	READ_D = 1 << 3,
};

typedef struct		s_readopt
{
	ssize_t 		timeout;
	char 			delim;
	ssize_t 		read_fd;
}					t_readopt;

static t_readopt	g_opt = {0, '\n', 0};

static inline int	parsearg(int ac, char *av[], uint8_t *flags)
{
	char	*a;
	int		i;

	i = 0;
	while (++i < ac)
		if (*av[i] == '-' && (a = av[i]))
			if (*++a  == 't' && (*flags |= READ_T))
				av[++i] ? g_opt.timeout = ft_atoi(av[i]) : 0;
			else if (*a == 'u' && (*flags |= READ_U))
				av[++i] ? g_opt.read_fd = ft_atoi(av[i]) : 0;
			else if (*a == 'd' && (*flags |= READ_D))
				av[++i] && ft_strlen(av[i]) == 1 ? g_opt.delim = av[i][0] : 0;
			else
				return (ft_retf(WUT, "read: %s: invalid option\n", a));
		else
			return (i);
	return (YEP);
}

inline static void	readarg(int ac, char **av, char *ln, int i)
{
	char	*chr;

	while (*ln && i < ac)
	{
		if (!(chr = ft_strmchr(ln, " \t\n")))
		{
			sh_varset(av[i], ln);
			break ;
		}
		if (i + 1 < ac)
		{
			*chr++ = '\0';
			while (ft_strchr(" \t\n", *chr))
				++chr;
		}
		sh_varset(av[i++], ln);
		ln = chr;
	}
}

inline int			sh_biread(int ac, char **av, char **env)
{
	struct termios	term;
	uint8_t			flags;
	ssize_t 		rd;
	t_ifs			ifs;
	char			*ln;
	int				i;

	(void)env;
	ft_ifsctor(&ifs, (int)g_opt.read_fd);
	flags = 0;
	if ((i = parsearg(ac, av, &flags)) < 0)
		return (EXIT_FAILURE);
	term.c_cc[VTIME] = (cc_t)(g_opt.timeout * 10);
	term.c_cc[VMIN] = (cc_t)(g_opt.timeout ? 0 : 1);
	term.c_cc[VEOL] = (cc_t)g_opt.delim;
	if ((rd = ft_ifschr(&ifs, 0, '\n', &ln)) < 0)
		return (EXIT_FAILURE);
	if (rd == 0)
		return (EXIT_SUCCESS);
	rd > 1 ? ln[rd - 1] = '\0' : 0;
	ac == i ? sh_varset("REPLY", ln) : readarg(ac, av, ln, i);
	ft_ifsdtor(&ifs);
	return (YEP);
}
