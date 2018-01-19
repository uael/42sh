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

static int	ft_getopt_long_longnoarg(t_opt *lopt, char *pname)
{
	if (g_optarg)
	{
		if (g_opterr)
			ft_putf(2, "%s: '--%s' doesn't allow an argument\n",
					pname, lopt->s);
		return ('?');
	}
	if (lopt->f)
		*lopt->f = lopt->val;
	return (lopt->f ? 0 : lopt->val);
}

static int	ft_getopt_long_longreqarg(t_opt *lopt, char **av,
										char *pname)
{
	if (!g_optarg)
		g_optarg = av[g_optind++];
	if (!g_optarg)
	{
		if (g_opterr)
			ft_putf(2, "%s: '--%s' options requires an argument\n",
					pname, lopt->s);
		return ('?');
	}
	if (lopt->f)
		*lopt->f = lopt->val;
	return (lopt->f ? 0 : lopt->val);
}

static int	ft_getopt_long_longoptarg(t_opt *lopt, char *pname)
{
	(void)pname;
	if (lopt->f)
		*lopt->f = lopt->val;
	return (lopt->f ? 0 : lopt->val);
}

int			ft_getopt_long_long(t_opt *lopt, char **av, char *pname)
{
	g_optind += 1;
	if (lopt == NULL)
		return ('?');
	else if (lopt->has_arg == no_arg)
		return (ft_getopt_long_longnoarg(lopt, pname));
	else if (lopt->has_arg == req_arg)
		return (ft_getopt_long_longreqarg(lopt, av, pname));
	else
		return (ft_getopt_long_longoptarg(lopt, pname));
}

void		ft_getopt_init(char **pname, char **nextchar, char *s)
{
	g_optind = 1;
	*pname = s;
	*nextchar = "";
}
