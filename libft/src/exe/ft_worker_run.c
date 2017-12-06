/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_worker_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 17:41:55 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/exe.h"

t_st			ft_worker_run(t_worker *self, int *status)
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
		if (waitpid(it->pid, &st, 0) < 0)
			return (ENO);
		if (WIFEXITED(st))
			it->st = WEXITSTATUS(st);
		if (it->cb)
			it->cb(it);
	}
	if (it > (t_job *)ft_vec_begin(self))
		--it;
	it ? *status = it->st : 0;
	return (0);
}
