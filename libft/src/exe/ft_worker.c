/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_worker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 19:52:30 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/exe.h"

inline void		ft_worker_ctor(t_worker *jobs)
{
	ft_vec_ctor(jobs, sizeof(t_job));
}

inline void		ft_worker_dtor(t_worker *self)
{
	ft_vec_dtor(self, (t_dtor)ft_job_dtor);
}

inline t_job	*ft_worker_push(t_worker *self, t_job *job)
{
	return ((t_job *)ft_vec_pushc(self, job));
}

t_st			ft_worker_run(t_worker *self, void *g, int *status)
{
	t_job	*it;
	int 	c[2];
	int 	d[2];
	int 	*p;
	t_st	st;

	p = NULL;
	it = (t_job *)ft_vec_begin(self) - 1;
	while (++it != (t_job *)ft_vec_end(self))
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
		if (waitpid(it->pid, &st, 0) < 0)
			return (ENO);
		if (WIFEXITED(st))
			it->st = WEXITSTATUS(st);
	}
	if (it > (t_job *)ft_vec_begin(self))
		--it;
	self->len = 0;
	it ? *status = it->st : 0;
	return (0);
}
