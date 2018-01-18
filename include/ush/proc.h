/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/proc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PROC_H
# define USH_PROC_H

# include "proc/state.h"
# include "proc/kind.h"
# include "redir.h"

typedef struct	s_proc
{
	pid_t		pid;
	t_procst	state;
	t_prockd	kind;
	int			status;
	char		**argv;
	char		**envv;
	int			io[3];
	t_redirs	redirs;
	t_procu		u;
}				t_proc;

typedef struct	s_procs
{
	t_proc		*buf;
	size_t		isz;
	size_t		cap;
	size_t		len;
}				t_procs;

extern void		sh_procctor(t_proc *proc);
extern void		sh_procdtor(t_proc *proc);
extern void		sh_proclaunch(t_proc *proc, pid_t pgid, int fg);
extern int		sh_procmark(t_proc *proc, int status);

#endif
