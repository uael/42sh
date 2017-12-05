/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_worker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 15:12:17 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/exe.h"

inline void		ft_worker_ctor(t_worker *jobs)
{
	ft_vec_ctor(jobs, sizeof(t_vec));
}

inline void		ft_worker_dtor(t_worker *jobs)
{
	ft_vec_dtor(jobs, (t_dtor)ft_job_dtor);
}

inline t_job	*ft_worker_push(t_worker *jobs, t_job *job, t_job_op next)
{
	job->op = next;
	return ((t_job *)ft_vec_pushc(jobs, job));
}

t_st			ft_worker_run(t_worker *jobs, void *g)
{
	t_job	*it;
	int 	c[2];
	int 	d[2];
	int 	*p;
	t_st	st;

	p = NULL;
	it = (t_job *)ft_vec_begin(jobs) - 1;
	while (++it != (t_job *)ft_vec_end(jobs))
	{
		if (it->op == JOB_OP_PIPE)
		{
			if (pipe(c))
				return (ENO);
			if (ST_NOK(st = ft_job_run(it, g, c, p)))
				return (st);
			p ? (void)(close(p[0]) & close(p[1])) : 0;
			p = memcpy(d, c, 2 * sizeof(int));
		}
		else if (it->op == JOB_OP_NONE)
		{
			if (ST_NOK(st = ft_job_run(it, g, NULL, p)))
				return (st);
			p ? (void)(close(p[0]) & close(p[1])) : 0;
		}
		if (it->kind == JOB_EXE && waitpid(it->u.pid, &st, 0) < 0)
			return (ENO);
		if (it->kind == JOB_EXE && WIFEXITED(st))
			it->st = WEXITSTATUS(st);
	}
	return (0);
}
