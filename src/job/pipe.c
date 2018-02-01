/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/pool.h"

inline void		sh_jobpipe(t_job *job, size_t i, int *fds, int *io)
{
	if (i < job->procs.len)
	{
		if (pipe(fds) < 0)
			sh_exit(THROW(WUT), NULL);
		io[STDOUT_FILENO] = fds[1];
	}
	else
	{
		fds[0] = 0;
		fds[1] = 0;
		io[STDOUT_FILENO] = STDOUT_FILENO;
	}
}
