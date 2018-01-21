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

char			**g_env = NULL;
static t_vec	g_venv_stack = { 0, sizeof(char *), 0, 0 };
static t_vec	*g_venv = &g_venv_stack;

inline void		sh_envdtor(void)
{
	ft_vecdtor(g_venv, (t_dtor)ft_pfree);
}

inline void		sh_envinit(char **envv)
{
	ssize_t	i;

	i = -1;
	if (envv)
		while (envv[++i])
			*(char **)ft_vecpush(g_venv) = ft_strdup(envv[i]);
	ft_vecgrow(g_venv, 1);
	ft_memset(ft_vecend(g_venv), 0, sizeof(char *));
	g_env = g_venv->buf;
}

inline char		*sh_getenv(char *var)
{
	char	**it;
	char	*val;

	it = g_env;
	while (*it && (!ft_strbegw(var, *it) || (*it)[ft_strlen(var)] != '='))
		++it;
	if (!*it || !(val = ft_strchr(*it, '=')))
		return (NULL);
	return (val + 1);
}

t_bool			sh_unsetenv(char *var, t_bool m)
{
	size_t	i;
	char	**it;

	if (!g_venv->len)
		return (0);
	i = 0;
	while (i < ft_veclen(g_venv))
		if ((it = ft_vecat(g_venv, i)) && *it &&
			ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
		{
			if (ft_vecrem(g_venv, i, it) && m)
				free(*it);
			g_env = g_venv->buf;
			return (1);
		}
		else
			++i;
	return (0);
}

void			sh_setenv(char *var, char *val)
{
	ft_setenv(g_venv, var, val);
	g_env = g_venv->buf;
}