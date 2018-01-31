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
#define N_ENV "env: "
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
					return (ft_retf(NOP, N_ENV"%c: "M_DUP"\n", *a) & 0);
				else if (ft_strchr("Pu", *a))
				{
					envgetopt(*a, *(a + 1) ? a + 1 : av[++i], (char **)o[1], e);
					break ;
				}
				else
					return (ft_retf(NOP, N_ENV"%c: %e\n", *a, EINVAL) & 0);
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

inline int		sh_bienv(int ac, char **av, char **env)
{
	int		i;
	int		s;
	uint8_t	flag;
	char	*alt;
	t_vec	e;

	ft_vecctor(&e, sizeof(char *));
	alt = NULL;
	if ((s = env_parse_opts(av, (void *[2]){&flag, &alt}, &e)) <= 0)
		return (ft_retf(NOP, EHELP));
	i = (ac & 0) -1;
	if (!(flag & ENV_I))
		while (env[++i])
			*(char **)ft_vecpush(&e) = ft_strdup(env[i]);
	*(char **)ft_vecpush(&e) = NULL;
	if (!*(av + s))
	{
		i = -1;
		env = e.buf;
		while (env[++i])
			ft_putl(STDOUT_FILENO, env[i]);
		free(e.buf);
		return (EXIT_SUCCESS);
	}
	return (env_finalize(alt ? alt : "PATH", av + s, e.buf));
}
