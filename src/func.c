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
#include "ush/shell.h"

inline void			sh_funcdtor(t_func *func)
{
	free((void *)func->ln);
	ft_deqdtor(&func->body, NULL);
	ft_bzero(func, sizeof(t_func));
}

inline void			sh_funcset(char const *name, t_deq *body, char const *ln)
{
	uint32_t	it;
	char		*dname;
	t_func		*fn;

	if (!body)
	{
		if (ft_mapget(&g_sh->funcs, (void *)name, &it))
			ft_mapdel(&g_sh->funcs, it);
		return ;
	}
	dname = NULL;
	if (!ft_mapget(&g_sh->funcs, (void *)name, &it) &&
		!ft_mapput(&g_sh->funcs, dname = ft_strdup(name), &it))
		return (dname ? free(dname) : (void)0);
	fn = &((t_func *)g_sh->funcs.vals)[it];
	ft_deqdtor(&fn->body, NULL);
	if (fn->ln)
		free((void *)fn->ln);
	fn->body = *body;
	fn->ln = ft_strdup(ln);
	ft_bzero(body, sizeof(t_deq));
}

inline t_func		*sh_funcget(char const *name)
{
	uint32_t	it;
	t_scope		*scope;

	scope = g_sh;
	while (scope)
	{
		if (ft_mapget(&scope->funcs, (void *)name, &it))
			return (&((t_func *)scope->funcs.vals)[it]);
		scope = scope->prev;
	}
	return (NULL);
}
