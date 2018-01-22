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

char 	*g_optarg = 0;
int		g_optind = 1;
int		g_optopt = 0;
int		g_opterr = 1;
int		g_optreset = 0;

int			illegal_option(const char *name, char c)
{
	if (g_opterr == 1)
		ft_putf(2, "%s: illegal option -- %c\n", name, c);
	return (-1);
}

int			isopt(char c, const char *optstring)
{
	if (ft_strchr(optstring, c))
		return (c);
	else
		return (0);
}

void		set_reset(int *is_over)
{
	if (g_optreset == 1)
	{
		*is_over = 0;
		g_optind = 1;
		g_optreset = 0;
	}
}

int			ft_getopt(int argc, const char **argv, const char *optstring)
{
	static int	is_over = 0;
	static int	i = 1;

	set_reset(&is_over);
	if (is_over == 1)
		return (-1);
	if (g_optind < argc && argv[g_optind][0] == '-' && argv[g_optind][1] != '-')
	{
		if ((g_optopt = isopt(argv[g_optind][i], optstring)))
		{
			if (argv[g_optind][++i] == 0 && (i = 1))
				g_optind++;
			return (g_optopt);
		}
		else
		{
			return (illegal_option(argv[0], argv[g_optind][i]));
		}
	}
	(g_optind < argc && argv[g_optind][0] == '-' && argv[g_optind][1] == '-') ?
		g_optind += 1 : 0;
	is_over = 1;
	g_optreset = 1;
	return (-1);
}
