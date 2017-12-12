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

#include "libft/exe.h"

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

static int	job_exec(t_job *self, int *wr, int *rd, int *dup)
{
	if (wr && (dup2(wr[1], STDOUT_FILENO) < 0 || close(wr[0]) || close(wr[1])))
		return (THROW(WUT));
	if (rd && (dup2(rd[0], STDIN_FILENO) < 0 || close(rd[0]) || close(rd[1])))
		return (THROW(WUT));
	if (dup[0] >= 0 && dup2(dup[0], STDIN_FILENO) < 0)
		return (THROW(WUT));
	if (dup[1] >= 0 && dup2(dup[1], STDOUT_FILENO) < 0)
		return (THROW(WUT));
	if (self->kind == JOB_FN)
		exit(self->fn(self->data, av_count(self->av), self->av, self->env));
	else
	{
		execve(self->av[0], self->av, self->env);
		exit(THROW(self->st = errno));
	}
}

int			ft_job_run(t_job *self, int *wr, int *rd)
{
	pid_t	pid;
	int		out;
	int		in;

	out = -1;
	in = -1;
	if (self->out &&
		(out = open(self->out, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(WUT));
	if (self->in &&
		(in = open(self->in, O_RDWR, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(WUT));
	if ((pid = fork()) < 0)
		return (THROW(WUT));
	if (pid == 0)
		return (job_exec(self, wr, rd, (int[2]){in, out}));
	if ((in >= 0 && close(in)) || (out >= 0 && close(out)))
		return (THROW(WUT));
	self->pid = pid;
	return (YEP);
}
