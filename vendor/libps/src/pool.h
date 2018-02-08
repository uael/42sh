/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libps/pool.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPS_POOL_H
# define LIBPS_POOL_H

# include "libps/job.h"

# ifndef CHILD_MAX
#  define CHILD_MAX 255
# endif

typedef struct	s_pool
{
	t_job		jobs[CHILD_MAX];
	size_t		len;
}				t_pool;

extern size_t	ps_poollen(void);
extern t_job	*ps_poolget(size_t idx);
extern t_bool	ps_poolrem(size_t idx, t_job *out);
extern int		ps_poolmark(pid_t pid, int status);
extern void		ps_poolnotify(void);

#endif
