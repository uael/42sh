/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/getopt.h"

char	*g_optarg = 0;
int		g_optind = 1;
int 	g_optopt = 0;
int 	g_opterr = 1;
int 	g_optreset = 0;

int 	treatment_opt(const char **av, int *i, const char *optstring, int *end)
{
	if (av[g_optind] && !av[g_optind][*i + 1])
		*end += 1;
	if (ft_strchr(optstring, av[g_optind][*i]))
	{
		*i += 1;
		g_optopt = av[g_optind][*i - 1];
		return (av[g_optind][*i - 1]);
	}
	else
	{
		if (g_opterr)
			ft_putf(1, "%s: illegal option -- %s\n", av[0],
				&(av[g_optind][*i]));
		*i += 1;
		g_optopt = av[g_optind][*i - 1];
		return ('?');
	}
}

void 	reset(int *i)
{
	g_optind++;
	*i = 1;
}

int 	ft_getopt(int ac, const char **av, const char *optstring)
{
	static int i = 1;
	static int end = 0;

	if (end)
	{
		reset(&i);
		end = 0;
	}
	if (ac >= 2)
	{
		if (av[g_optind] && av[g_optind][0] == '-' && av[g_optind][1] == '-')
		{
			g_optind++;
			return (-1);
		}
		if (av[g_optind] && av[g_optind][0] == '-' && av[g_optind][1] == '\0')
			return (-1);
		else if (av[g_optind] && av[g_optind][i] == '\0' &&
			av[g_optind][0] == '-')
			reset(&i);
		if (av[g_optind] && av[g_optind][i] && av[g_optind][0] == '-' &&
			av[g_optind][i] != '-')
			return (treatment_opt(av, &i, optstring, &end));
	}
	return (-1);
}

