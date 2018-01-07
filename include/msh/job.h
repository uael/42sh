/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/job.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_JOB_H
# define MSH_JOB_H

# include "proc.h"

typedef struct	s_job
{
	struct s_job	*next;
	char			*command;
	t_proc			*prochead;
	pid_t			pgid;
	t_bool			notified;
	TTY				tmodes;
	int				io[3];
}				t_job;

extern t_job	*g_jobhead;

extern t_job	*sh_jobfind(pid_t pgid);
extern int		sh_jobstopped(t_job *j);
extern int		sh_jobcompleted(t_job *j);
extern void		sh_joblaunch(t_job *j, int fg);
extern void		sh_jobdebug(t_job *j, const char *status);
extern void		sh_jobwait(t_job *j);
extern void		sh_jobnotify(void);
extern void		sh_jobfg(t_job *j, int cont);
extern void		sh_jobbg(t_job *j, int cont);
extern void		sh_jobcontinue(t_job *j, int fg);

#endif
