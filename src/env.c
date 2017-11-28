/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 12:34:46 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline t_st		msh_initenv(t_msh *self, char **env)
{
	char	**it;
	ssize_t	i;

	i = -1;
	if (env)
		while (env[++i])
		{
			if (!(it = ft_vstr_push(&self->env)))
				return (ENO);
			else if (!(*it = ft_strdup(env[i])))
				return (ENO);
		}
	if (!ft_vstr_grow(&self->env, 1))
		return (ENO);
	FT_INIT(ft_vstr_end(&self->env), char *);
	return (OK);
}

inline char		**msh_getenv(t_msh *self, char *var)
{
	char **it;

	if (!self->env.len || !(it = ft_vstr_begin(&self->env)))
		return (NULL);
	while (it && it != ft_vstr_end(&self->env))
		if (*it && ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
			return (it);
		else
			++it;
	return (NULL);
}

inline t_st		msh_unsetenv(t_msh *self, char *var)
{
	size_t	i;
	char	**it;
	t_bool	r;

	if (!self->env.len)
		return (NOK);
	i = 0;
	while (i < ft_vstr_size(&self->env))
		if ((it = ft_vstr_at(&self->env, i)) && *it &&
			ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
		{
			if ((r = ft_vstr_remove(&self->env, i, it)))
				free(*it);
			return (r ? OK : ENO);
		}
		else
			++i;
	return (NOK);
}

inline t_st		msh_setenv(t_msh *self, char *var, char *val)
{
	char **it;

	if ((it = msh_getenv(self, var)))
		free(*it);
	else if (!(it = ft_vstr_push(&self->env)))
		return (ENO);
	if (!(*it = malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2)
		* sizeof(char))))
		return (ENO);
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	if (!ft_vstr_grow(&self->env, 1))
		return (ENO);
	FT_INIT(ft_vstr_end(&self->env), char *);
	return (OK);
}

inline t_st		msh_envadd(t_msh *self, char *var, char *val)
{
	char **it;

	if (msh_getenv(self, var))
		return (OK);
	else if (!(it = ft_vstr_push(&self->env)))
		return (ENO);
	if (!(*it = malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2)
		* sizeof(char))))
		return (ENO);
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	if (!ft_vstr_grow(&self->env, 1))
		return (ENO);
	FT_INIT(ft_vstr_end(&self->env), char *);
	return (OK);
}
