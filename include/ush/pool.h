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

extern t_pool	*g_pool;
extern size_t	g_scopelvl;

extern void		sh_poolscope(void);
extern t_bool	sh_poolunscope(void);
extern t_job	*sh_pooladd(t_job *job);
extern t_job	*sh_poolfind(pid_t pgid);
extern int		sh_poolmark(pid_t pid, int status);
extern void		sh_poolnotify(void);
extern void		sh_poolclean(void);

#endif
