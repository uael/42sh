/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/pool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_POOL_H
# define USH_POOL_H

# include "job.h"

typedef struct	s_pool
{
	t_job		jobs[CHILD_MAX];
	size_t		len;
}				t_pool;

extern size_t	sh_poollen(void);
extern t_job	*sh_poolget(size_t idx);
extern t_job	*sh_poolpush(t_job *job);
extern t_bool	sh_poolrem(size_t idx, t_job *out);
extern int		sh_poolmark(pid_t pid, int status);
extern void		sh_poolnotify(void);

#endif
