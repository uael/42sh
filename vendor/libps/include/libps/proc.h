/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libps/proc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/18 17:39:21 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPS_PROC_H
# define LIBPS_PROC_H

#include "libft/ft_glob.h"
# include "proc/bi.h"
# include "proc/bit.h"
# include "proc/err.h"
# include "proc/exe.h"
# include "proc/fn.h"
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
	PROC_BI,
	PROC_FN,
	PROC_ERR,
	PROC_BIT
}				t_prockd;

typedef union	u_procu
{
	t_procexe	exe;
	t_procbi	*bi;
	t_procfn	fn;
	t_procerr	err;
	t_procbit	bit;
}				t_procu;

typedef struct	s_proc
{
	pid_t		pid;
	t_procst	state;
	t_prockd	kind;
	int			status;
	T_GLOB		argv;
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

extern void		ps_procctor(t_proc *proc);
extern void		ps_procdtor(t_proc *p);
extern int		ps_procfork(t_proc *p, pid_t *pgid, int *io, int fg);

#endif
