/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_ctor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 18:30:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cmd.h"

inline void		ft_job_fn(t_job *self, t_job_fn fn, char **av, char **env)
{
	FT_INIT(self, t_job);
	ft_vec_ctor(&self->dups, sizeof(t_dup2));
	self->kind = JOB_FN;
	self->av = av;
	self->env = env;
	self->fn = fn;
	self->pin = STDIN_FILENO;
	self->pout = STDOUT_FILENO;
}

static int		job_output(void *s, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	ft_puts(1, (char *)s);
	return (0);
}

inline void		ft_job_output(t_job *self, char *str)
{
	FT_INIT(self, t_job);
	ft_vec_ctor(&self->dups, sizeof(t_dup2));
	self->kind = JOB_FN;
	self->fn = job_output;
	self->data = str;
	self->pin = STDIN_FILENO;
	self->pout = STDOUT_FILENO;
}
