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

#include "msh/env.h"

char			**g_env = NULL;
static t_vec	g_venv_stack = { 0, sizeof(char *), 0, 0 };
static t_vec	*g_venv = &g_venv_stack;

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

void			sh_setenv(char *var, char *val)
{
	char **it;

	if (!g_venv->len || !(it = ft_vecbeg(g_venv)))
		return ;
	while (it && it != ft_vecend(g_venv))
		if (!*it || !ft_strbegw(var, *it) || (*it)[ft_strlen(var)] != '=')
			++it;
		else
		{
			ft_pfree((void **)it);
			break ;
		}
	if (!it || *it)
		it = ft_vecpush(g_venv);
	*it = ft_malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2) *
		sizeof(char));
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	ft_vecgrow(g_venv, 1);
	ft_memset(ft_vecend(g_venv), 0, sizeof(char *));
	g_env = g_venv->buf;
}
