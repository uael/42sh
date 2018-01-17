/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/pool.h"

static t_vec	g_pools_stack = { NULL, sizeof(t_pool), 0, 0 };
static t_vec	*g_pools = &g_pools_stack;
t_pool			*g_pool = NULL;

inline void		sh_poolscope(void)
{
	g_pool = ft_vecpush(g_pools);
	if (!g_pool->isz)
		ft_vecctor((t_vec *)g_pool, sizeof(t_job));
}

/*
** TODO: check for running jobs
*/

inline t_bool	sh_poolunscope(void)
{
	if (g_pool && ft_vecpop(g_pools, NULL))
	{
		ft_vecdtor((t_vec *)g_pool, (t_dtor)sh_jobdtor);
		g_pool = ft_vecback(g_pools);
		return (1);
	}
	ft_vecdtor(g_pools, NULL);
	return (0);
}

inline t_job	*sh_poolfind(pid_t pgid)
{
	size_t	i;
	t_job	*job;

	if (!g_pool)
		return (NULL);
	i = 0;
	while (i < g_pool->len)
		if ((job = g_pool->jobs + i++)->pgid == pgid)
			return (job);
	return (NULL);
}
