/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 10:43:23 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"
#include "msh/env.h"

#define ENV_I (1 << 0)
#define ENV_P (0)
#define ENV_U (1)
#define M_DUP "Duplicate option"
#define N_ENV COLOR_RED COLOR_BOLD "env: " COLOR_RESET

static void		env_get_opt(char o, char *a, char **opt)
{
	if (o == 'P')
		opt[ENV_P] = a;
	else if (o == 'u')
		opt[ENV_U] = a;
}

static int		env_parse_opts(t_sh *sh, char **av, void **o, t_vstr *e)
{
	int		i;
	char	*a;

	i = 0;
	while ((a = av[++i]))
		if (*a == '-')
		{
			while (*++a)
				if (*a == 'i' && !(*((uint8_t *)o[0]) & ENV_I))
					*((uint8_t *)o[0]) |= ENV_I;
				else if (*a == 'i')
					return (sh_bi_zretf(sh, 0, N_ENV"%c: "M_DUP"\n", *a));
				else if (ft_strchr("Pu", *a))
					env_get_opt(*a, *(a + 1) ? a + 1 : av[++i], (char **)o[1]);
				else
					return (sh_bi_zretf(sh, 0, N_ENV"%c: %e\n", *a, EINVAL));
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

static t_st		env_finalize(t_sh *sh, char *path, char ***vars, t_job *out)
{
	int		s;
	t_vstr	av;

	if (!vars[0] || !*vars[0])
		return (OK);
	ft_vstr_ctor(&av);
	while (*vars[0])
		if (!ft_vstr_pushc(&av, *vars[0]++))
			return (ENO);
	av.buf[0] = ft_strdup(av.buf[0]);
	if (ST_NOK(s = ft_job_exe(out, path, av.buf, vars[1])))
	{
		if (ISE(s))
			sh_bi_retf(sh, NOK, N_ENV"%s: %e\n", av.buf[0], ST_TOENO(s));
		else
			sh_bi_retf(sh, NOK, N_ENV"%s: Command not found\n", av.buf[0]);
		free(av.buf[0]);
		free(vars[1]);
		ft_vstr_dtor(&av, NULL);
		return (NOK);
	}
	return (OK);
}

inline t_st		sh_bi_env(t_sh *sh, int ac, char **av, t_job *out)
{
	int		i;
	int		s;
	uint8_t	flag;
	char	*opt[2];
	t_vstr	e;

	(void)sh;
	ft_vstr_ctor(&e);
	ft_memset(opt, flag = 0, 2 * sizeof(char *));
	if ((s = env_parse_opts(sh, av, (void *[2]){&flag, opt}, &e)) <= 0)
		return (SZ_TOST(s));
	if ((s == (i = -1) + 2 && s == ac) || !(flag & ENV_I))
		while (++i < (int)sh->env.len)
		{
			if (s == 1 && s == ac)
				ft_omstream_putl(&sh->bi_out, sh->env.buf[i]);
			else if (!ft_vstr_pushc(&e, sh->env.buf[i]))
				return (ENO);
		}
	if ((s == 1 && s == ac) || !ft_vstr_pushc(&e, NULL))
		return ((s == 1 && s == ac) ? OK : ENO);
	if (opt[ENV_U] && ISE(s = sh_unsetenv(&e, opt[ENV_U], 0)))
		return ((t_st)s);
	return (env_finalize(sh, opt[ENV_P] ? opt[ENV_P] : "PATH",
		(char **[2]){av + s, e.buf}, out));
}
