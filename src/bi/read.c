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

inline static void	readarg(int ac, char **av, char *ln)
{
	int		i;
	char	*chr;

	i = 0;
	while (*ln && ++i < ac)
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
		sh_varset(av[i], ln);
		ln = chr;
	}
}

inline int			sh_biread(int ac, char **av, char **env)
{
	ssize_t rd;
	t_ifs	ifs;
	char	*ln;

	(void)env;
	ft_ifsctor(&ifs, STDIN_FILENO);
	if ((rd = ft_ifschr(&ifs, 0, '\n', &ln)) < 0)
		return (EXIT_FAILURE);
	if (rd == 0)
		return (EXIT_SUCCESS);
	rd > 1 ? ln[rd - 1] = '\0' : 0;
	ac == 1 ? sh_varset("REPLY", ln) : readarg(ac, av, ln);
	ft_ifsdtor(&ifs);
	return (YEP);
}
