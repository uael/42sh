/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 17:50:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/exe.h"

inline void		ft_job_cb(t_job *self, t_job_cb cb)
{
	self->cb = cb;
}

inline void		ft_job_data(t_job *self, void *data)
{
	self->data = data;
}

inline void		ft_job_pipe(t_job *self)
{
	self->pipe = 1;
}
