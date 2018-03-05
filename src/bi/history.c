/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/bi/history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/bi.h"
#include "ush/env.h"
#include "ush/shell.h"

static inline void	optinit(t_histopt *opts)
{
	opts->flags = 0;
	opts->offset = 0;
	opts->filename = ".ushst";
	opts->arg = NULL;
}

static inline int	histparse(int ac, char *av[], t_histopt *opts)
{
	int		opt;

	g_optind = 1;
	optinit(opts);
	while ((opt = ft_getopt(ac, av, "cr:a:w:d:p:s:")) != -1)
		if (opt == 'r' && (opts->flags |= HISTORY_R))
			opts->filename = g_optarg;
		else if (opt == 'a' && (opts->flags |= HISTORY_A))
			opts->filename = g_optarg;
		else if (opt == 'w' && (opts->flags |= HISTORY_W))
			opts->filename = g_optarg;
		else if (opt == 'd' && (opts->flags |= HISTORY_D))
			opts->offset = (uint8_t)ft_atoi(g_optarg);
		else if (opt == 'c')
			opts->flags |= HISTORY_C;
		else if (opt == 'p' && (opts->flags |= HISTORY_P))
			opts->arg = g_optarg;
		else if (opt == 's' && (opts->flags |= HISTORY_S))
			opts->arg = g_optarg;
		else
			return (WUT);
	return (g_optind);
}

inline int			sh_bihistory(int ac, char **av, char **env)
{
	char		*home;
	char		buf[PATH_MAX];
	t_histopt	opt;
	size_t		len;

	(void)env;
	if (!g_sh->tty || histparse(ac, av, &opt) < 0)
		return (EXIT_FAILURE);
	if (opt.flags & HISTORY_C)
		rl_histdtor();
	else if (opt.offset && (opt.flags & HISTORY_D))
		rl_histdel(opt.offset);
	else if (opt.filename && ((opt.flags & HISTORY_W) || opt.flags & HISTORY_A))
		(home = sh_getenv("HOME")) ? rl_histsave(ft_pathcat(ft_strcpy(buf,
		home), opt.filename)) : 0;
	else if (opt.filename && (opt.flags & HISTORY_R))
		(home = sh_getenv("HOME")) ? rl_histload(ft_pathcat(ft_strcpy(buf,
		home), opt.filename)) : 0;
	else if (opt.arg && (opt.flags & HISTORY_S) && (len = strlen(opt.arg)) &&
		(opt.arg[len] = '\n'))
		rl_histadd(opt.arg, len + 1);
	else if (ac == 1)
		rl_histdump();
	return (EXIT_SUCCESS);
}
