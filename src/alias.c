/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/alias.h"

static t_map	g_alias_stack =
{
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(char *), NULL, NULL
};
static t_map	*g_alias = &g_alias_stack;

inline int		sh_aliasdump(void)
{
	uint32_t	it;
	char		*val;

	it = 0;
	while (it < g_alias->cap)
	{
		if (!(g_alias->bucks[it] & BUCKET_BOTH))
		{
			val = ((char **)g_alias->vals)[it];
			ft_putf(STDOUT_FILENO, ft_strlen(val) ? "alias %s='%s'\n" :
				"alias %s=''\n",
				((char **)g_alias->keys)[it], val);
		}
		++it;
	}
	return (YEP);
}

inline void		sh_aliasdtor(void)
{
	ft_mapdtor(g_alias, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
}

inline void		sh_aliasset(char const *alias, char const *val)
{
	uint32_t	it;
	char		*dalias;

	if (!val)
	{
		if (ft_mapget(g_alias, (void *)alias, &it))
			ft_mapdel(g_alias, it);
	}
	else if (ft_mapget(g_alias, (void *)alias, &it))
	{
		free(((char **)g_alias->vals)[it]);
		((char **)g_alias->vals)[it] = ft_strdup(val);
	}
	else if (ft_mapput(g_alias, dalias = ft_strdup(alias), &it))
		((char **)g_alias->vals)[it] = ft_strdup(val);
	else
		free(dalias);
}

inline char		*sh_aliasget(char const *alias)
{
	uint32_t	it;

	if (ft_mapget(g_alias, (void *)alias, &it))
		return (((char **)g_alias->vals)[it]);
	return (NULL);
}
