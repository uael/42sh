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

inline t_st		sh_initenv(t_vstr *self, char **env)
{
	char	**it;
	ssize_t	i;

	i = -1;
	if (env)
		while (env[++i])
		{
			if (!(it = ft_vstr_push(self)))
				return (ENO);
			else if (!(*it = ft_strdup(env[i])))
				return (ENO);
		}
	if (!ft_vstr_grow(self, 1))
		return (ENO);
	FT_INIT(ft_vstr_end(self), char *);
	return (OK);
}

inline char		**sh_getenv(t_vstr *self, char *var)
{
	char **it;

	if (!self->len || !(it = ft_vstr_begin(self)))
		return (NULL);
	while (it && it != ft_vstr_end(self))
		if (*it && ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
			return (it);
		else
			++it;
	return (NULL);
}

inline t_st		sh_unsetenv(t_vstr *self, char *var, t_bool m)
{
	size_t	i;
	char	**it;
	t_bool	r;

	if (!self->len)
		return (NOK);
	i = 0;
	while (i < ft_vstr_size(self))
		if ((it = ft_vstr_at(self, i)) && *it &&
			ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
		{
			if ((r = ft_vstr_remove(self, i, it)) && m)
				free(*it);
			return (r ? OK : ENO);
		}
		else
			++i;
	return (NOK);
}

inline t_st		sh_setenv(t_vstr *self, char *var, char *val)
{
	char **it;

	if ((it = sh_getenv(self, var)))
		free(*it);
	else if (!(it = ft_vstr_push(self)))
		return (ENO);
	if (!(*it = malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2)
		* sizeof(char))))
		return (ENO);
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	if (!ft_vstr_grow(self, 1))
		return (ENO);
	FT_INIT(ft_vstr_end(self), char *);
	return (OK);
}

inline t_st		sh_envadd(t_vstr *self, char *var, char *val)
{
	char **it;

	if (sh_getenv(self, var))
		return (OK);
	else if (!(it = ft_vstr_push(self)))
		return (ENO);
	if (!(*it = malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2)
		* sizeof(char))))
		return (ENO);
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	if (!ft_vstr_grow(self, 1))
		return (ENO);
	FT_INIT(ft_vstr_end(self), char *);
	return (OK);
}
