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

inline t_ret	msh_initenv(t_msh *self, char **env)
{
	char	**it;
	ssize_t	i;

	i = -1;
	if (env)
		while (env[++i])
		{
			if (!(it = ft_vstr_push(&self->env)))
				return (RET_ERR);
			else if (!(*it = ft_strdup(env[i])))
				return (RET_ERR);
		}
	if (!ft_vstr_grow(&self->env, 1))
		return (RET_ERR);
	FT_INIT(ft_vstr_end(&self->env), char *);
	return (RET_OK);
}

inline char		**msh_getenv(t_msh *self, char *var)
{
	char **it;

	if (!self->env.len || !(it = ft_vstr_begin(&self->env)))
		return (NULL);
	while (it && it != ft_vstr_end(&self->env))
		if (ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
			return (it);
		else
			++it;
	return (NULL);
}

inline t_ret	msh_unsetenv(t_msh *self, char *var)
{
	size_t	i;
	char	**it;
	t_bool	r;

	if (!self->env.len)
		return (RET_NOK);
	i = 0;
	while (i < ft_vstr_size(&self->env))
		if ((it = ft_vstr_at(&self->env, i)) &&
			ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
		{
			if ((r = ft_vstr_remove(&self->env, i, it)))
				free(*it);
			return (r ? RET_OK : RET_ERR);
		}
		else
			++i;
	return (RET_NOK);
}

inline t_ret	msh_setenv(t_msh *self, char *var, char *val)
{
	char **it;

	if ((it = msh_getenv(self, var)))
		free(*it);
	else if (!(it = ft_vstr_push(&self->env)))
		return (RET_ERR);
	if (!(*it = malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2)
		* sizeof(char))))
		return (RET_ERR);
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	if (!ft_vstr_grow(&self->env, 1))
		return (RET_ERR);
	FT_INIT(ft_vstr_end(&self->env), char *);
	return (RET_OK);
}

inline t_ret	msh_envadd(t_msh *self, char *var, char *val)
{
	char **it;

	if (msh_getenv(self, var))
		return (RET_OK);
	else if (!(it = ft_vstr_push(&self->env)))
		return (RET_ERR);
	if (!(*it = malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2)
		* sizeof(char))))
		return (RET_ERR);
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	if (!ft_vstr_grow(&self->env, 1))
		return (RET_ERR);
	FT_INIT(ft_vstr_end(&self->env), char *);
	return (RET_OK);
}
