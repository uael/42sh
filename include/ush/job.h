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

typedef struct	s_job
{
	pid_t		pgid;
	char		*command;
	char		**envv;
	t_procs		pipeline;
	t_bool		notified;
	TTY			tmodes;
	int			io[3];
	t_redirs	redirs;
	t_bool		bang;
	t_bool		bg;
	t_bool		and;
	t_bool		or;
}				t_job;

extern void		sh_jobdtor(t_job *job);
extern int		sh_jobstopped(t_job *j);
extern int		sh_jobcompleted(t_job *j);
extern void		sh_joblaunch(t_job *job, int fg);
extern void		sh_jobwait(t_job *j);
extern void		sh_jobfg(t_job *j, int cont);
extern void		sh_jobbg(t_job *j, int cont);
extern void		sh_jobcont(t_job *j, int fg);

#endif
