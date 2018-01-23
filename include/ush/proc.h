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

# include "proc/kind.h"
# include "proc/sh.h"
# include "proc/state.h"
# include "redir.h"

# define PROC_NOTFOUND (127)
# define PROC_NORIGHTS (126)

typedef struct	s_proc
{
	pid_t		pid;
	t_procst	state;
	t_prockd	kind;
	int			status;
	char		**argv;
	char		**envv;
	t_bool		ownenv;
	int			scope[3];
	int			src[3];
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

extern int		sh_procctor(t_proc *proc, char *path, char *exe, char **envv);
extern void		sh_procdtor(t_proc *proc);
extern int		sh_procmark(t_proc *proc, int status);
extern int		sh_proclaunch(t_proc *proc, pid_t pgid, int *io, int fg);
extern void		sh_procfn(t_proc *proc, t_procfn *fn, char **envv);
extern int		sh_procfnlaunch(t_proc *proc, pid_t pid);
extern void		sh_proccnf(t_proc *proc, char *ln, t_tok *tok, int st);
extern int		sh_proccnflaunch(t_proc *proc);
extern int		sh_procsh(t_proc *proc, t_deq *toks, char *ln);
extern int		sh_procshlaunch(t_proc *proc, pid_t pid);
extern void		sh_procbool(t_proc *proc, t_bool boolean);
extern int		sh_procboollaunch(t_proc *proc, pid_t pid);

#endif
