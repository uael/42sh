/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job/debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/job.h"

inline void		sh_jobdebug(t_job *j, const char *status)
{
	sh_err("%ld (%s): %s\n", (long) j->pgid, status, j->command);
}
