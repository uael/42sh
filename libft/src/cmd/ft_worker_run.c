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

#ifdef __CYGWIN__
# include <wait.h>
#endif

#include "libft/cmd.h"

int				ft_worker_join(t_worker *self)
{
	t_job	*it;
	int		st;

	it = (t_job *)ft_vec_end(self);
	while (--it >= (t_job *)ft_vec_begin(self))
	{
		if (it->pid <= 0)
			continue ;
		while (waitpid(it->pid, &st, 0) < 0)
			if (errno != EINTR)
				return (THROW(WUT));
		if (WIFEXITED(st))
			it->st = WEXITSTATUS(st);
		if (it->cb)
			it->cb(it);
	}
	return (ft_vec_size(self) ? ((t_job *)ft_vec_back(self))->st : 0);
}

int				ft_worker_run(t_worker *self)
{
	t_job	*it;
	int		c[2];
	int		d[2];
	int		*p;

	p = NULL;
	it = (t_job *)ft_vec_begin(self) - 1;
	while (++it != (t_job *)ft_vec_end(self))
		if (it->pipe)
		{
			if (pipe(c))
				return (THROW(WUT));
			if (ft_job_run(it, c, p))
				return (WUT);
			if (p && (close(p[0]) || close(p[1])))
				return (THROW(WUT));
			p = ft_memcpy(d, c, 2 * sizeof(int));
		}
		else if (ft_job_run(it, NULL, p))
			return (WUT);
		else if (p && (close(p[0]) || close(p[1])))
			return (THROW(WUT));
	return (0);
}
