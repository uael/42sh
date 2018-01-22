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

int			g_optind;
char		*g_optarg;
int			g_opterr = 1;

t_opt				*ft_opt_getstruct_long(char *s,
		t_opt 	*longopt,
		char 	*pname)
{
	char	*has_arg;
	size_t	ncmp;

	has_arg = ft_strchr(s, '=');
	if (has_arg)
		g_optarg = has_arg + 1;
	ncmp = (size_t)has_arg ? (size_t)(has_arg - s) : ft_strlen(s);
	while (longopt->s != NULL)
	{
		if (ncmp == ft_strlen(longopt->s) &&
				!ft_strncmp(s, longopt->s, ncmp))
			break ;
		longopt++;
	}
	if (longopt->s == NULL)
	{
		if (g_opterr)
			ft_putf(2, "%s: unrecognized options '--%.*s'\n", pname,
					(int)ncmp, s);
		return (NULL);
	}
	return (longopt);
}

t_opt				*ft_opt_getstruct(char s, t_opt *longopt)
{
	while (longopt->s != NULL)
	{
		if (s == longopt->val)
			break ;
		longopt++;
	}
	return (longopt->s ? longopt : NULL);
}

static int			ft_opt_end(char **nextchar)
{
	*nextchar = NULL;
	return (-1);
}

static int			ft_getopt_(char **nextchar, char **av,
		t_opt *lopt)
{
	if (lopt->has_arg == req_arg && (*nextchar)[1] == 0)
		g_optarg = av[g_optind++];
	return (*(*nextchar)++);
}

int					ft_lgetopt(int ac, char **av, char *optstr, t_opt *lopt)
{
	static char			*nextchar;
	static char			*pname;

	g_optarg = 0;
	if (g_optind == 0)
		ft_getopt_init(&pname, &nextchar, av[0]);
	if (nextchar == NULL)
		return (-1);
	if ((*nextchar == 0 && g_optind >= ac) || av[g_optind] == 0 ||
		OPT_ISEND(av[g_optind]))
		return (ft_opt_end(&nextchar));
	else if (*nextchar == 0 && OPT_ISLONG(av[g_optind]))
		return (ft_llgetopt(
			ft_opt_getstruct_long(av[g_optind] + 2, lopt, pname), av, pname));
	else if (*nextchar == 0 && OPT_ISOPT(av[g_optind]))
		nextchar = av[g_optind++] + 1;
	else if (*nextchar == 0)
		return (ft_opt_end(&nextchar));
	if (optstr && ft_strchr(optstr, *nextchar))
		return (ft_getopt_(&nextchar, av, ft_opt_getstruct(*nextchar, lopt)));
	if (g_opterr)
		ft_putf(2, "%s: unrecognized option '%c'\n", pname, *nextchar++);
	return ('?');
}
