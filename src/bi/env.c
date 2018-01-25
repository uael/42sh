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
#define ENV_P (0)
#define ENV_U (1)
#define M_DUP "Duplicate option"
#define N_ENV COLOR_RED COLOR_BOLD "env: " COLOR_RESET
#define EHELP1 "usage: env [-iv] [-P utilpath] [-u name]\n"
#define EHELP EHELP1 "           [name=value ...] [utility [argument ...]]\n"

static void		env_get_opt(char o, char *a, char **opt)
{
	if (o == 'P')
		opt[ENV_P] = a;
	else if (o == 'u')
		opt[ENV_U] = a;
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
					return (ft_retf(0, N_ENV"%c: "M_DUP"\n", *a));
				else if (ft_strchr("Pu", *a))
					env_get_opt(*a, *(a + 1) ? a + 1 : av[++i], (char **)o[1]);
				else
					return (ft_retf(0, N_ENV"%c: %e\n", *a, EINVAL));
		}
		else if (ft_strchr(a, '='))
			*(char **)ft_vecpush(e) = ft_strdup(a);
		else
			break ;
	return (i);
}

static int		env_finalize(char *path, char **argv, char **envv)
{
	int		s;
	t_vec	av;
	t_proc	proc;
	t_job	*job;

	if ((s = sh_procctor(&proc, path, argv[0], envv)))
	{
		sh_proccnf(&proc, NULL, NULL, s);
		proc.u.cnf.exe = argv[0];
	}
	else
	{
		ft_vecctor(&av, sizeof(char *));
		while (*argv)
			*(char **)ft_vecpush(&av) = ft_strdup(*argv++);
		*(char **)ft_vecpush(&av) = NULL;
		proc.argv = av.buf;
	}
	proc.ownenv = 1;
	sh_jobctor(job = alloca(sizeof(t_job)));
	*(t_proc *)ft_vecpush((t_vec *)&job->procs) = proc;
	s = sh_joblaunch(&job, 1);
	job->idx < 0 ? sh_jobdtor(job) : 0;
	return (job->idx < 0 ? 1 : s);
}

static int		env_rmvar(t_vec *env, char *var)
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

inline int		sh_bienv(int ac, char **av, char **env)
{
	int		i;
	int		s;
	uint8_t	flag;
	char	*opt[2];
	t_vec	e;

	ft_vecctor(&e, sizeof(char *));
	ft_memset(opt, flag = 0, 2 * sizeof(char *));
	if ((s = env_parse_opts(av, (void *[2]){&flag, opt}, &e)) <= 0)
		return (ft_retf(NOP, EHELP));
	if ((s == (i = -1) + 2 && s == ac) || !(flag & ENV_I))
		while (env[++i])
		{
			if (s == 1 && s == ac)
				ft_putl(1, env[i]);
			else
				*(char **)ft_vecpush(&e) = ft_strdup(env[i]);
		}
	if (s == 1 && s == ac)
		return (YEP);
	*(char **)ft_vecpush(&e) = NULL;
	opt[ENV_U] ? env_rmvar(&e, opt[ENV_U]) : 0;
	if (!*(av + s))
		return (EXIT_SUCCESS);
	return (env_finalize(opt[ENV_P] ? opt[ENV_P] : "PATH", av + s, e.buf));
}
