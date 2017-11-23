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
	while (env[++i])
		if (!(it = ft_vstr_push(&self->env)))
			return (RET_ERR);
		else if (!(*it = ft_strdup(env[i])))
			return (RET_ERR);
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
	while (it != ft_vstr_end(&self->env) && it)
		if (ft_strbegw(var, *(it++), '='))
			return (it - 1);
	return (NULL);
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
