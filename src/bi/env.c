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

#include "ush.h"

#define ENV_I (1 << 0)
#define M_DUP "Duplicate option"
#define ENV "env: "
#define EHELP1 "usage: env [-i] [-P utilpath] [-u name]\n"
#define EHELP EHELP1 "           [name=value ...] [utility [argument ...]]\n"

static int		envrmvar(t_vec *env, char *var)
{
	size_t	i;
	char	**it;

	if (!env->len)
		return (0);
	i = 0;
	while (i < ft_veclen(env))
		if ((it = ft_vecat(env, i)) && *it &&
			ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
		{
			ft_vecrem(env, i, it);
			free(*it);
			g_env = env->buf;
			return (1);
		}
		else
			++i;
	return (0);
}

static void		envgetopt(char o, char *a, char **alt, t_vec *e)
{
	if (o == 'P')
		*alt = a;
	else if (!ft_strchr(a, '='))
		envrmvar(e, a);
}

static int		env_parse_opts(char **av, void **o, t_vec *e)
{
	int			i;
	char		*a;

	i = 0;
	while ((a = av[++i]))
		if (*a == '-')
		{
			while (*++a)
				if (*a == 'i' && !(*((uint8_t *)o[0]) & ENV_I))
					*((uint8_t *)o[0]) |= ENV_I;
				else if (*a == 'i')
					return (ft_retf(NOP, ENV"%c: "M_DUP"\n", *a) & 0);
				else if (ft_strchr("Pu", *a))
				{
					envgetopt(*a, *(a + 1) ? a + 1 : av[++i], (char **)o[1], e);
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

	sh_procexe(&proc, path, argv[0], envv);
	ft_vecctor(&av, sizeof(char *));
	while (*argv)
		*(char **)ft_vecpush(&av) = ft_strdup(*argv++);
	*(char **)ft_vecpush(&av) = NULL;
	proc.argv = av.buf;
	proc.ownenv = 1;
	sh_jobctor(job = alloca(sizeof(t_job)));
	*(t_proc *)ft_vecpush((t_vec *)&job->procs) = proc;
	return (sh_joblaunch(job, 1));
}

inline int		sh_bienv(int ac, char **av, char **ev)
{
	int		i;
	int		s;
	uint8_t	flag;
	char	*alt;
	t_vec	ve;

	ft_vecctor(&ve, sizeof(char *));
	flag = 0;
	alt = NULL;
	if ((s = env_parse_opts(av, (void *[2]){&flag, &alt}, &ve)) <= 0)
		return (ft_retf(NOP, EHELP));
	i = (ac & 0) - 1;
	if (!(flag & ENV_I))
		while (ev[++i])
			*(char **)ft_vecpush(&ve) = ft_strdup(ev[i]);
	*(char **)ft_vecpush(&ve) = NULL;
	if (!*(av + s) && (i = -1))
	{
		ev = ve.buf;
		while (ev[++i])
			(void)(ft_putl(STDOUT_FILENO, ev[i]) && ft_pfree((void **)&ev[i]));
		free(ve.buf);
		return (EXIT_SUCCESS);
	}
	return (env_finalize(alt ? alt : "PATH", av + s, ve.buf));
}
