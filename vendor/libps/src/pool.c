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

#include "ps.h"

static t_pool	g_async_stack;
static t_pool	*g_async = &g_async_stack;

inline size_t	ps_poollen(void)
{
	return (g_async->len);
}

inline t_job	*ps_poolget(size_t idx)
{
	if (idx > g_async->len)
		return (NULL);
	return (g_async->jobs + idx);
}

inline t_job	*ps_poolpush(t_job *job)
{
	t_job *bg;

	bg = ft_memcpy(g_async->jobs + g_async->len, job, sizeof(t_job));
	bg->idx = (int)g_async->len++;
	bg->bg = 1;
	return (bg);
}

inline t_bool	ps_poolrem(size_t idx, t_job *out)
{
	t_job *job;

	if (idx > g_async->len)
		return (0);
	if (out)
		ft_memcpy(out, g_async + idx, sizeof(t_job));
	if (--g_async->len)
	{
		ft_memmove(g_async->jobs + idx, g_async->jobs + idx + 1,
			sizeof(t_job) * (g_async->len - idx));
		while (idx < g_async->len)
		{
			job = g_async->jobs + idx++;
			job->idx = (int)idx;
		}
	}
	return (1);
}
