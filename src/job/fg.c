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

inline void		sh_jobfg(t_job *j, int cont)
{
	tcsetpgrp(STDIN_FILENO, j->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			sh_err("kill (SIGCONT): %e\n", errno);
	}
	sh_jobwait(j);
	tcsetpgrp(STDIN_FILENO, g_shpgid);
	tcgetattr(STDIN_FILENO, &j->tmodes);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shmode);
}
