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

static inline int	parsearg(int ac, char *av[], uint8_t *flags)
{
	int		i;
	char	*a;

	i = 0;
	while (++i < ac)
		if (*av[i] == '-' && (a = av[i]))
			while (*++a)
				if (*a == 't')
					*flags |= READ_T;
				else if (*a == 'u')
					*flags |= READ_U;
				else if (*a == 'd')
					*flags |= READ_D;
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
	ssize_t rd;
	t_ifs	ifs;
	char	*ln;
	int		i;
	uint8_t	flags;

	(void)env;
	ft_ifsctor(&ifs, STDIN_FILENO);
	flags = 0;
	if ((i = parsearg(ac, av, &flags)) < 0)
		return (EXIT_FAILURE);
	if ((flags & READ_T))
		;
	if ((rd = ft_ifschr(&ifs, 0, '\n', &ln)) < 0)
		return (EXIT_FAILURE);
	if (rd == 0)
		return (EXIT_SUCCESS);
	rd > 1 ? ln[rd - 1] = '\0' : 0;
	ac == 1 ? sh_varset("REPLY", ln) : readarg(ac, av, ln, i);
	ft_ifsdtor(&ifs);
	return (YEP);
}
