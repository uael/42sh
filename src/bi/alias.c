/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/alias.h"
#include "ush/bi.h"

static char const	*g_usage = "usage: alias [-p] [name[=value] …]\n"
"\tWithout arguments or with the -p option, alias prints the list of aliases\n"
"\ton the standard output in a form that allows them to be reused as input.\n"
"\tIf arguments are supplied, an alias is defined for each name whose value\n"
"\tis given. If no value is given, the name and value of the alias is dumped\n";

static int	aliasopt(int ac, char **av)
{
	int		opt;
	t_bool	p;

	p = 0;
	g_optind = 1;
	while ((opt = ft_getopt(ac, av, "p")) != -1)
		if (opt == 'p')
		{
			if (!p)
			{
				sh_aliasdump();
				p = 1;
			}
		}
		else
			return (WUT);
	if (g_optind == ac && !p)
		sh_aliasdump();
	return (g_optind);
}

inline int	sh_bialias(int ac, char **av)
{
	int		i;
	char	*eq;
	char	*alias;

	if ((i = aliasopt(ac, av)) < 1)
		return (ft_retf(EXIT_FAILURE, g_usage));
	while (i < ac)
	{
		if ((eq = ft_strchr(av[i], '=')))
		{
			*eq = '\0';
			sh_aliasset(av[i], ft_strdup(eq + 1));
		}
		else if (!(alias = sh_aliasget(av[i])))
			ft_putf(STDERR_FILENO, "alias: %s: Not found\n", av[i]);
		else
			ft_putf(STDOUT_FILENO, "alias %s='%s'\n", av[i], alias);
		++i;
	}
	return (EXIT_SUCCESS);
}
