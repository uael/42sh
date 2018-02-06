/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libps/job.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPS_JOB_H
# define LIBPS_JOB_H

#include <librl.h>

# include "proc.h"
# include "redir.h"

# ifndef CHILD_MAX
#  define CHILD_MAX (256)
# endif

typedef enum	e_andor
{
	ANDOR_NONE,
	ANDOR_AND,
	ANDOR_OR
}				t_andor;

typedef struct	s_jb
{
	int			idx;
	struct s_jb	*next;
	t_andor		andor;
	pid_t		pgid;
	char		*command;
	t_procs		procs;
	t_bool		bang;
	t_bool		bg;
	TTY			tmodes;
}				t_job;

extern void		ps_jobctor(t_job *job);
extern void		ps_jobdtor(t_job *job);
extern int		ps_jobstopped(t_job *j);
extern int		ps_jobcompleted(t_job *j);
extern void		ps_jobpipe(t_job *job, size_t i, int *fds, int *io);
extern int		ps_joblaunch(t_job *job, int fg);
extern int		ps_jobmark(t_job *job, pid_t pid, int status);
extern void		ps_jobwait(t_job *job);
extern int		ps_jobfg(t_job *job, int cont);
extern int		ps_jobbg(t_job *job, int cont);
extern void		ps_jobcont(t_job *job, int fg);
extern void		ps_jobdebug(t_job *job);

#endif
