/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 15:46:36 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lib.h"
#include "libft/str.h"
#include "libft/ds.h"

inline char		*ft_getenv(char **env, char *var)
{
	char *val;

	while (*env && (!ft_strbegw(var, *env) || (*env)[ft_strlen(var)] != '='))
		++env;
	if (!*env || !(val = ft_strchr(*env, '=')))
		return (NULL);
	return (val + 1);
}

inline void		ft_setenv(t_vec *env, char *var, char *val)
{
	char **it;

	if (!env->len || !(it = ft_vecbeg(env)))
		return ;
	while (it != ft_vecend(env))
		if (!*it || !ft_strbegw(var, *it) || (*it)[ft_strlen(var)] != '=')
			++it;
		else
		{
			free(*it);
			break ;
		}
	if (!*it)
		it = ft_vecpush(env);
	*it = ft_malloc((ft_strlen(var) + (val ? ft_strlen(val) : 0) + 2) *
		sizeof(char));
	ft_strcpy(*it, var);
	(!ft_strrchr(*it, '=') ? ft_strcat(*it, "=") : NULL);
	(val ? ft_strcat(*it, val) : NULL);
	ft_vecgrow(env, 1);
	ft_memset(ft_vecend(env), 0, sizeof(char *));
}
