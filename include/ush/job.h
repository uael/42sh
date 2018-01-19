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

typedef enum	e_andor
{
	ANDOR_NONE,
	ANDOR_AND,
	ANDOR_OR
}				t_andor;

typedef struct	s_jb
{
	struct s_jb	*next;
	int			status;
	t_andor		andor;
	pid_t		pgid;
	char		*command;
	t_procs		processes;
	t_bool		notified;
	TTY			tmodes;
}				t_job;

extern void		sh_jobctor(t_job *job);
extern void		sh_jobdtor(t_job *job);
extern int		sh_jobstopped(t_job *j);
extern int		sh_jobcompleted(t_job *j);
extern int		sh_joblaunch(t_job *job, int fg);
extern int		sh_jobmark(t_job *job, pid_t pid, int status);
extern void		sh_jobwait(t_job *job);
extern void		sh_jobfg(t_job *j, int cont);
extern void		sh_jobbg(t_job *job, int cont);
extern void		sh_jobcont(t_job *j, int fg);
extern void		sh_jobdebug(t_job *job);

#endif
