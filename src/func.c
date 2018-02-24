/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/func.h"

static t_map	g_funcs_stack =
{
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(t_func), NULL, NULL
};
static t_map	*g_funcs = &g_funcs_stack;

static inline void	funcdtor(t_func *func)
{
	free((void *)func->ln);
	ft_deqdtor(&func->body, NULL);
	ft_bzero(func, sizeof(t_func));
}

inline void			sh_funcdtor(void)
{
	ft_mapdtor(g_funcs, (t_dtor)ft_pfree, (t_dtor)funcdtor);
}

inline void			sh_funcset(char const *name, t_deq *body, char const *ln)
{
	uint32_t	it;
	char		*dname;

	if (!body)
	{
		if (ft_mapget(g_funcs, (void *)name, &it))
			ft_mapdel(g_funcs, it);
		return ;
	}
	if (ft_mapget(g_funcs, (void *)name, &it))
	{
		funcdtor(&((t_func *)g_funcs->vals)[it]);
		dname = ((char **)g_funcs->keys)[it];
	}
	else if (!ft_mapput(g_funcs, dname = ft_strdup(name), &it))
		return (free(dname));
	((char **)g_funcs->vals)[it] = dname;
	((t_func *)g_funcs->vals)[it].body = *body;
	((t_func *)g_funcs->vals)[it].name = dname;
	((t_func *)g_funcs->vals)[it].ln = ft_strdup(ln);
	ft_bzero(body, sizeof(t_deq));
}

inline t_func		*sh_funcget(char const *name)
{
	uint32_t	it;

	if (ft_mapget(g_funcs, (void *)name, &it))
		return (&((t_func *)g_funcs->vals)[it]);
	return (NULL);
}
