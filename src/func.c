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
	if (func->next)
		funcdtor(func->next);
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
	t_func		*fn;

	if (!body)
	{
		if (ft_mapget(g_funcs, (void *)name, &it))
			ft_mapdel(g_funcs, it);
		return ;
	}
	dname = NULL;
	if (!ft_mapget(g_funcs, (void *)name, &it) &&
		!ft_mapput(g_funcs, dname = ft_strdup(name), &it))
		return (dname ? free(dname) : (void)0);
	fn = &((t_func *)g_funcs->vals)[it];
	while (fn->next)
		fn = fn->next;
	if (fn->ln)
	{
		ft_bzero(fn->next = ft_malloc(sizeof(t_func)), sizeof(t_func));
		fn = fn->next;
	}
	fn->body = *body;
	fn->ln = ft_strdup(ln);
	ft_bzero(body, sizeof(t_deq));
}

inline t_func		*sh_funcget(char const *name)
{
	uint32_t	it;
	t_func		*fn;

	if (ft_mapget(g_funcs, (void *)name, &it))
	{
		fn = &((t_func *)g_funcs->vals)[it];
		while (fn->next)
			fn = fn->next;
		return (fn);
	}
	return (NULL);
}
