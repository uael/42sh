/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/env.h"

static t_vec	g_venv_stack = { 0, sizeof(char *), 0, 0 };
static t_vec	*g_venv = &g_venv_stack;

#define PATH_DFL "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

inline void		sh_envdtor(void)
{
	ft_vecdtor(g_venv, (t_dtor)ft_pfree);
}

inline void		sh_envinit(char **envv)
{
	ssize_t	i;
	t_bool	hasp;

	i = -1;
	hasp = 0;
	if (envv)
		while (envv[++i])
		{
			*(char **)ft_vecpush(g_venv) = ft_strdup(envv[i]);
			if (ft_strbegw("PATH", envv[i]) && envv[i][4] == '=')
				hasp = 1;
		}
	if (!hasp)
		*(char **)ft_vecpush(g_venv) = ft_strdup(PATH_DFL);
	*(char **)ft_vecpush(g_venv) = NULL;
	--g_venv->len;
	g_env = g_venv->buf;
}

inline char		*sh_getenv(char *var)
{
	return (ft_getenv(g_env, var));
}

t_bool			sh_unsetenv(char *var, t_bool m)
{
	t_bool ret;

	if ((ret = ft_unsetenv(g_venv, var, m)))
		g_env = g_venv->buf;
	return (ret);
}

void			sh_setenv(char *var, char *val)
{
	ft_setenv(g_venv, var, val);
	g_env = g_venv->buf;
}
