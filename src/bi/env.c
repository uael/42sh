/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush.h"

#define ENV "env: "
#define EHELP1 "usage: env [-i] [-P utilpath] [-u name]\n"
#define EHELP EHELP1 "           [name=value ...] [utility [argument ...]]\n"

static void		envgetopt(char o, char *a, char **altpath, t_vec *e)
{
	if (o == 'P')
		*altpath = a;
	else if (!ft_strchr(a, '='))
		ft_unsetenv(e, a, 1);
}

static int		env_parse_opts(char **av, char **altpath, t_vec *e)
{
	int			i;
	char		*a;

	i = 0;
	while ((a = av[++i]))
		if (*a == '-')
		{
			while (*++a)
				if (*a == 'i')
					ft_vecclr(e, (t_dtor)ft_pfree);
				else if (ft_strchr("Pu", *a))
				{
					envgetopt(*a, *(a + 1) ? a + 1 : av[++i], altpath, e);
					break ;
				}
				else
					return (ft_retf(NOP, ENV"%c: %e\n", *a, EINVAL) & 0);
		}
		else if (ft_strchr(a, '='))
			*(char **)ft_vecpush(e) = ft_strdup(a);
		else
			break ;
	return (i);
}

static int		env_finalize(char *path, char **argv, char **envv)
{
	t_vec	av;
	t_proc	proc;
	t_job	*job;

	ps_procctor(&proc);
	ps_procexe(&proc, path, argv[0], envv);
	ft_vecctor(&av, sizeof(char *));
	while (*argv)
		*(char **)ft_vecpush(&av) = ft_strdup(*argv++);
	*(char **)ft_vecpush(&av) = NULL;
	proc.argv = av.buf;
	proc.ownenv = 1;
	ps_jobctor(job = alloca(sizeof(t_job)));
	*(t_proc *)ft_vecpush((t_vec *)&job->procs) = proc;
	return (ps_joblaunch(job, 1));
}

inline int		sh_bienv(int ac, char **av, char **ev)
{
	int		i;
	int		s;
	char	*alt;
	t_vec	ve;

	(void)ac;
	ft_vecctor(&ve, sizeof(char *));
	alt = NULL;
	i = -1;
	while (ev[++i])
		*(char **)ft_vecpush(&ve) = ft_strdup(ev[i]);
	if ((s = env_parse_opts(av, &alt, &ve)) <= 0)
		return (ft_retf(NOP, EHELP));
	*(char **)ft_vecpush(&ve) = NULL;
	if (!*(av + s))
	{
		i = -1;
		ev = ve.buf;
		while (ev[++i])
			(void)(ft_putl(STDOUT_FILENO, ev[i]) && ft_pfree((void **)&ev[i]));
		free(ve.buf);
		return (EXIT_SUCCESS);
	}
	return (env_finalize(alt ? alt : "PATH", av + s, ve.buf));
}
