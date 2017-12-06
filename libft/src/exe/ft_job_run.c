/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 19:58:51 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "libft/exe.h"

static int	av_count(char **av)
{
	char **beg;

	beg = av;
	while (*av)
		++av;
	return ((int)(av - beg));
}

t_st 		ft_job_run(t_job *self, void *g, int *write, int *read)
{
	pid_t pid;

	if ((pid = fork()) < 0)
		return (ENO);
	if (pid == 0)
	{
		if (write)
		{
			close(write[0]);
			dup2(write[1], STDOUT_FILENO);
		}
		if (read)
		{
			close(read[1]);
			dup2(read[0], STDIN_FILENO);
		}
		if (self->kind == JOB_FN)
			exit(self->fn(g, av_count(self->av), self->av, self->env));
		else
		{
			execve(self->av[0], self->av, self->env);
			return (ENO);
		}
	}
	return ((self->pid = pid) & 0);
}
