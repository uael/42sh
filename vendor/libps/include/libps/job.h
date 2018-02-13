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

# include <librl.h>

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
extern void		ps_jobkill(t_job *job);
extern int		ps_joblaunch(t_job *job, int fg);
extern t_job	*ps_jobnext(t_job *job, t_job *next, t_andor andor);
extern t_job	*ps_poolpush(t_job *job);

#endif
