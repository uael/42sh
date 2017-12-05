/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 16:41:30 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"
#include "msh/env.h"

#define ENV_I (1 << 0)
#define ENV_P (0)
#define ENV_U (1)
#define M_DUP "Duplicate option"

static void		env_get_opt(char o, char *a, char **opt)
{
	if (o == 'P')
		opt[ENV_P] = a;
	else if (o == 'u')
		opt[ENV_U] = a;
}

static int	env_parse_opts(int ac, char **av, void **o, t_vstr *e)
{
	int		i;
	char	*a;

	i = 0;
	while (++i < ac && (a = av[i]))
		if (*a == '-')
		{
			while (*++a)
				if (*a == 'i' && !(*((uint8_t *)o[0]) & ENV_I))
					*((uint8_t *)o[0]) |= ENV_I;
				else if (*a == 'i')
					return (ft_szret(0, "%s: "M_DUP" '%c'", "env", *a));
				else if (ft_strchr("Pu", *a))
					env_get_opt(*a, *(a + 1) ? a + 1 : av[++i], (char **)o[1]);
				else
					return (ft_szret(0, "%s: %e '%c'", "env", EINVAL, *a));
		}
		else if (ft_strchr(a, '='))
		{
			if (!ft_vstr_pushc(e, a))
				return (ENO);
		}
		else
			break ;
	return (i);
}

static t_st		env_run(char *path, char **av, char **env)
{
	t_st	st;
	t_job	job;

	if (ST_NOK(st = ft_job_exe(&job, path, av, env)))
		return (st);
	return (ft_job_run(&job, NULL, NULL, NULL));
}

inline t_st		sh_bi_env(t_sh *sh, int ac, char **av, char **env)
{
	int		sz;
	uint8_t	flag;
	char	*opt[2];
	t_vstr	e;

	(void)sh;
	ft_vstr_ctor(&e);
	ft_memset(opt, flag = 0, 2 * sizeof(char *));
	if ((sz = env_parse_opts(ac, av, (void *[2]){&flag, opt}, &e)) <= 0)
		return (SZ_TOST(sz));
	if ((sz == 1 && sz == ac) || !(flag & ENV_I))
		while (*env++)
		{
			if (sz == 1 && sz == ac)
				ft_putl(1, *(env - 1));
			else if (!ft_vstr_pushc(&e, *(env - 1)))
				return (ENO);
		}
	if (sz == 1 && sz == ac)
		return (OK);
	if (opt[ENV_U] && ISE(sz = sh_unsetenv(&e, opt[ENV_U], 0)))
		return ((t_st)sz);
	sz = env_run(opt[ENV_P] ? opt[ENV_P] : "PATH", av + sz, e.buf);
	ft_vstr_dtor(&e, NULL);
	return ((t_st)sz);
}
