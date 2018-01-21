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

#include "ush/var.h"

static t_vec	g_scopes = { NULL, sizeof(t_map), 0, 0 };
static t_map	*g_scope = NULL;

void sh_vardump()
{
	t_map		*scope;
	uint32_t it;

	scope = ft_vecpush(&g_scopes);
	it = 0;
	while (it < g_scope->len)
	{
		if (BUCKET_ISPOPULATED(g_scope->bucks, it))
			ft_putl(1, ((char **)g_scope->vals)[it]);
		++it;
	}
	g_scope = scope;
}

inline void		sh_varscope(void)
{
	t_map		*scope;
	uint32_t	it;
	uint32_t	put;

	scope = ft_vecpush(&g_scopes);
	if (!scope->ksz)
		ft_mapctor(scope, g_strhash, sizeof(char *), sizeof(char *));
	it = 0;
	if (g_scope)
		while (it < g_scope->len)
		{
			if (BUCKET_ISPOPULATED(g_scope->bucks, it) &&
				ft_mapput(scope, ((char **)g_scope->keys)[it], &put))
				((char **)scope->vals)[put] =
					ft_strdup(((char **)g_scope->vals)[it]);
			++it;
		}
	g_scope = scope;
}

inline t_bool	sh_varunscope(void)
{
	if (g_scope && ft_vecpop(&g_scopes, NULL))
	{
		ft_mapdtor(g_scope, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
		g_scope = ft_vecback(&g_scopes);
		return (1);
	}
	ft_vecdtor(&g_scopes, NULL);
	return (0);
}

inline void		sh_varset(char *var, char *val)
{
	uint32_t	it;

	if (ft_mapget(g_scope, var, &it) || ft_mapput(g_scope, ft_strdup(var), &it))
		((char **)g_scope->vals)[it] = ft_strdup(val);
}

inline char        *sh_varget(char *var)
{
	uint32_t	it;

	if (ft_mapget(g_scope, var, &it))
		return (((char **)g_scope->vals)[it]);
	return (sh_getenv(var));
}
