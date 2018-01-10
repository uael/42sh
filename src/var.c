/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/env.h"

static t_vec	g_scopes = { NULL, sizeof(t_map), 0, 0 };
static t_map	*g_scope = NULL;

inline void		sh_scopepush(void)
{
	g_scope = ft_vecpush(&g_scopes);
	if (!g_scope->ksz)
		ft_mapctor(g_scope, g_strhash, sizeof(char *), sizeof(char *));
}

inline t_bool	sh_scopepop(void)
{
	if (g_scope && ft_vecpop(&g_scopes, NULL))
	{
		ft_mapdtor(g_scope, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
		g_scope = ft_vecback(&g_scopes);
		return (1);
	}
	return (0);
}

inline void		sh_varset(char *var, char *val)
{
	uint32_t	it;

	if (ft_mapget(g_scope, var, &it) || ft_mapput(g_scope, ft_strdup(var), &it))
		((char **)g_scope->vals)[it] = ft_strdup(val);
}

inline char		*sh_varget(char *var)
{
	uint32_t	it;

	if (ft_mapget(g_scope, var, &it))
		return (((char **)g_scope->vals)[it]);
	return (NULL);
}
