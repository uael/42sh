/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/job.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_JOB_H
# define USH_JOB_H

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
	t_bool		notified;
	t_bool		bang;
	t_bool		bg;
	TTY			tmodes;
}				t_job;

extern void		sh_jobctor(t_job *job);
extern void		sh_jobdtor(t_job *job);
extern int		sh_jobstopped(t_job *j);
extern int		sh_jobcompleted(t_job *j);
extern int		sh_joblaunch(t_job *job, int fg);
extern int		sh_jobmark(t_job *job, pid_t pid, int status);
extern void		sh_jobwait(t_job *job);
extern int		sh_jobfg(t_job *job, int cont);
extern void		sh_jobbg(t_job *job, int cont);
extern void		sh_jobcont(t_job *job, int fg);
extern void		sh_jobdebug(t_job *job);

#endif
