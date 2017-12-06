/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_worker_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 19:39:27 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/exe.h"

int				ft_worker_join(t_worker *self)
{
	t_job	*it;
	t_st	st;

	it = (t_job *)ft_vec_end(self);
	while (--it >= (t_job *)ft_vec_begin(self))
	{
		if (it->pid <= 0)
			continue ;
		if (waitpid(it->pid, &st, 0) < 0)
			return (ENO);
		if (WIFEXITED(st))
			it->st = WEXITSTATUS(st);
		if (it->cb)
			it->cb(it);
	}
	return (ft_vec_size(self) ? ((t_job *)ft_vec_back(self))->st : 0);
}

t_st			ft_worker_run(t_worker *self)
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
		if (it->pipe)
		{
			if (pipe(c))
				return (ENO);
			if (ST_NOK(st = ft_job_run(it, c, p)))
				return (st);
			p ? (void)(close(p[0]) & close(p[1])) : 0;
			p = memcpy(d, c, 2 * sizeof(int));
		}
		else
		{
			if (ST_NOK(st = ft_job_run(it, NULL, p)))
				return (st);
			p ? (void)(close(p[0]) & close(p[1])) : 0;
		}
	}
	return (0);
}
