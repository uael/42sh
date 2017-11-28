/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:31:34 by null             ###   ########.fr       */
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

static ssize_t	env_parse_opts(t_vstr *av, uint8_t *flag, char **opt, t_vstr *e)
{
	size_t	i;
	char	*a;

	i = 0;
	while (++i < av->len && (a = av->buf[i]))
		if (*a == '-')
		{
			while (*++a)
				if (*a == 'i' && !(*flag & ENV_I))
					*flag |= ENV_I;
				else if (*a == 'i')
					return (ft_szret(0, "%s: "M_DUP" '%c'", "env", *a));
				else if (ft_strchr("Pu", *a))
					env_get_opt(*a, *(a + 1) ? a + 1 : av->buf[++i], opt);
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

static t_st		env_flush(t_st st, t_vstr *env)
{
	ft_vstr_dtor(env, NULL);
	return (st);
}

inline t_st		sh_bi_env(t_sh *s, t_vstr *av)
{
	size_t	i;
	ssize_t	sz;
	uint8_t	flag;
	char	*opt[2];
	t_vstr	e;

	ft_vstr_ctor(&e);
	ft_memset(opt, flag = 0, 2 * sizeof(char *));
	if ((sz = env_parse_opts(av, &flag, opt, &e)) <= 0)
		return (SZ_TOST(sz));
	if ((sz == (i = 0) + 1 && (size_t)sz == av->len) || !(flag & ENV_I))
		while (i < s->env.len)
		{
			if (s->env.buf[i++] && sz == 1 && (size_t)sz == av->len)
				ft_putl(1, s->env.buf[i - 1]);
			else if (s->env.buf[i - 1] && !ft_vstr_pushc(&e, s->env.buf[i - 1]))
				return (ENO);
		}
	if (sz == 1 && (size_t)sz == av->len)
		return (OK);
	if (opt[ENV_U] && ISE(sz = sh_unsetenv(&e, opt[ENV_U], 0)))
		return ((t_st)sz);
	ft_vstr_shiftn(av, (size_t)sz, NULL);
	return (env_flush(sh_exe_run(s, opt[ENV_P] ? opt[ENV_P] : "PATH", av, &e),
		&e));
}
