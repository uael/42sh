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

# include "proc/bit.h"
# include "proc/err.h"
# include "proc/exe.h"
# include "proc/fn.h"
# include "proc/sh.h"
# include "redir.h"

typedef enum	e_procst
{
	PROC_COMPLETED,
	PROC_STOPPED,
	PROC_RUNNING,
	PROC_CONTINUED
}				t_procst;

typedef enum	e_prockd
{
	PROC_NONE,
	PROC_EXE,
	PROC_FN,
	PROC_SH,
	PROC_ERR,
	PROC_BOOL
}				t_prockd;

typedef union	u_procu
{
	t_procexe	exe;
	t_procfn	*fn;
	t_procsh	sh;
	t_procerr	err;
	t_procbit	bit;
}				t_procu;

typedef struct	s_proc
{
	pid_t		pid;
	t_procst	state;
	t_prockd	kind;
	int			status;
	char		**argv;
	char		**envv;
	t_bool		ownenv;
	t_bool		child;
	t_bool		piped;
	int			scope[3];
	int			src[3];
	int			close;
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
extern void		sh_procdtor(t_proc *p);
extern int		sh_procmark(t_proc *proc, int status);
extern int		sh_proclaunch(t_proc *proc, pid_t pgid, int *io, int fg);

#endif
