/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 07:15:25 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline void		sh_initenv(t_vstr *self, char **env)
{
	ssize_t	i;

	i = -1;
	if (env)
		while (env[++i])
			*ft_vstr_push(self) = ft_strdup(env[i]);
	ft_vstr_grow(self, 1);
	FT_INIT(ft_vstr_end(self), char *);
}

inline t_bool	sh_unsetenv(t_vstr *self, char *var, t_bool m)
{
	size_t	i;
	char	**it;

	if (!self->len)
		return (FALSE);
	i = 0;
	while (i < ft_vstr_size(self))
		if ((it = ft_vstr_at(self, i)) && *it &&
			ft_strbegw(var, *it) && (*it)[ft_strlen(var)] == '=')
		{
			if (ft_vstr_remove(self, i, it) && m)
				free(*it);
			return (YEP);
		}
		else
			++i;
	return (FALSE);
}

inline void		sh_setenv(t_vstr *self, char *var, char *val)
{
	char **it;

	if (!self->len || !(it = ft_vstr_begin(self)))
		return ;
	while (it && it != ft_vstr_end(self))
		if (!*it || !ft_strbegw(var, *it) || (*it)[ft_strlen(var)] != '=')
			++it;
		else
		{
			ft_pfree((void **)it);
			break ;
		}
	if (!it || *it)
		it = ft_vstr_push(self);
	*it = ft_malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2) *
		sizeof(char));
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	ft_vstr_grow(self, 1);
	FT_INIT(ft_vstr_end(self), char *);
}

inline t_bool	sh_envadd(t_vstr *self, char *var, char *val)
{
	char **it;

	if (!self->len || !(it = ft_vstr_begin(self)))
		return (FALSE);
	while (it && it != ft_vstr_end(self))
		if (!*it || !ft_strbegw(var, *it) || (*it)[ft_strlen(var)] != '=')
			++it;
		else
			return (FALSE);
	it = ft_vstr_push(self);
	*it = ft_malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2) *
		sizeof(char));
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	ft_vstr_grow(self, 1);
	FT_INIT(ft_vstr_end(self), char *);
	return (TRUE);
}
