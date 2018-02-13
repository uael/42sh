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

#define	BADCH	(int)'?'
#define	BADARG	(int)':'
#define	EMSG	""
#define ERR0 "%s: illegal option -- %c\n"
#define ERR1 "%s: option requires an argument -- %c\n"

char		*g_optarg = 0;
int			g_optind = 1;
int			g_optopt = 0;
int			g_opterr = 1;
static int	g_optreset = 0;
static char	*g_place = EMSG;

static int	getopt2(char const *oli, int ac, char *av[], char const *fmt)
{
	if (g_optopt == ':' || (oli = ft_strchr(fmt, g_optopt)) == NULL)
	{
		!*g_place ? ++g_optind : 0;
		g_opterr && *fmt != ':' ? ft_putf(2, ERR0, av[0], g_optopt) : 0;
		return (BADCH);
	}
	if (oli[1] != ':')
		*g_place == (char)(g_optarg = NULL) ? ++g_optind : 0;
	else
	{
		if (*g_place)
			g_optarg = g_place;
		else if (ac > ++g_optind)
			g_optarg = av[g_optind];
		else
		{
			if ((g_place = EMSG) && *fmt == ':')
				return (BADARG);
			g_opterr ? ft_putf(STDERR_FILENO, ERR1, av[0], g_optopt) : 0;
			return (BADCH);
		}
		g_place = EMSG;
		++g_optind;
	}
	return (g_optopt);
}

int			ft_getopt(int ac, char *av[], char const *fmt)
{
	char *str;

	g_place = EMSG;
	str = NULL;
	if (g_optreset || *g_place == 0)
	{
		g_optreset = 0;
		g_place = av[g_optind];
		if ((g_optind >= ac || *g_place++ != '-') && (g_place = EMSG))
			return (WUT);
		g_optopt = *g_place++;
		if (g_optopt == '-' && *g_place == 0 && (g_place = EMSG) && ++g_optind)
			return (WUT);
		if (g_optopt == 0 && (g_place = EMSG))
		{
			if (ft_strchr(fmt, '-') == NULL)
				return (WUT);
			else
				g_optopt = '-';
		}
	}
	else
		g_optopt = *g_place++;
	return (getopt2(str, ac, av, fmt));
}
