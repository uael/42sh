/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 12:42:46 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "libft/cmd.h"

static int	av_count(char **av)
{
	char **beg;

	if (!av || !*av)
		return (0);
	beg = av;
	while (*av)
		++av;
	return ((int)(av - beg));
}

static int	job_exec(t_job *self, int *wr, int *rd)
{
	t_dup2	*dup;

	if (wr && (dup2(wr[1], self->pout) < 0 || close(wr[0]) || close(wr[1])))
		return (THROW(WUT));
	if (rd && (dup2(rd[0], self->pin) < 0 || close(rd[0]) || close(rd[1])))
		return (THROW(WUT));
	if (ft_vec_size(&self->dups) && (dup = (t_dup2 *)ft_vec_begin(&self->dups)))
		while (dup != (t_dup2 *)ft_vec_end(&self->dups))
		{
			if ((*dup).to < 0)
				close((*dup).from);
			else if (dup2((*dup).to, (*dup).from) < 0 || close((*dup).to))
				exit(THROW(self->st = errno));
			++dup;
		}
	if (self->kind == JOB_FN)
		exit(self->fn(self->data, av_count(self->av), self->av, self->env));
	else
	{
		execve(self->av[0], self->av, self->env);
		exit(THROW(self->st = errno));
	}
}

int			ft_job_run(t_job *job, int *wr, int *rd)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		return (THROW(WUT));
	if (pid == 0)
		return (job_exec(job, wr, rd));
	job->pid = pid;
	return (YEP);
}
