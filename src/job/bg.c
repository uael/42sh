/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/fg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "ush/job.h"

inline void		sh_jobbg(t_job *job, int cont)
{
	job->bg = 1;
	g_shstatus = 0;
	if (cont && kill(-job->pgid, SIGCONT) < 0)
		sh_err("kill (SIGCONT): %e\n", errno);
}
