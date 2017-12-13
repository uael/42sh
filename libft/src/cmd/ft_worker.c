/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_worker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 11:48:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cmd.h"

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

inline void		ft_worker_clear(t_worker *self)
{
	ft_vec_clear(self, (t_dtor)ft_job_dtor);
}
