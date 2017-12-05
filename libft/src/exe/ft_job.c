/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 15:07:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "libft/exe.h"

inline void ft_job_fn(t_job *self, t_job_fn fn, char **av, char **env)
{
	FT_INIT(self, t_job);
	self->kind = JOB_FN;
	self->av = av;
	self->env = env;
	self->u.fn = fn;
}

inline void ft_job_dtor(t_job *self)
{
	if (self->kind == JOB_EXE)
		free(self->av[0]);
	free(self->av[0]);
}