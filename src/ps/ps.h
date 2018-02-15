/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include <librl.h>
# include <libft.h>

# include "ush/ps.h"
# include "pool.h"

extern t_map		*g_binaries;
extern t_map		*g_builtins;
extern t_errcb		*g_errcb;
extern t_fatalcb	*g_fatalcb;
extern t_bool		g_tty;
extern pid_t		g_pgid;
extern pid_t		g_pid;
extern TTY			g_tcmode;

extern int			ps_bibg(int ac, char **av, char **env);
extern int			ps_bifg(int ac, char **av, char **env);
extern int			ps_bijobs(int ac, char **av, char **env);

extern int			ps_redirect(t_redirs *redirs, int *scope);
extern void			ps_redirectclose(t_redirs *redirs);

extern int			ps_procmark(t_proc *proc, int status);
extern int			ps_proclaunch(t_proc *proc, pid_t pgid, int *io, int fg);

extern int			ps_jobstopped(t_job *j);
extern int			ps_jobcompleted(t_job *j);
extern void			ps_jobpipe(t_job *job, size_t i, int *fds, int *io);
extern int			ps_jobmark(t_job *job, pid_t pid, int status);
extern void			ps_jobwait(t_job *job);
extern int			ps_jobfg(t_job *job, int cont);
extern int			ps_jobbg(t_job *job, int cont);
extern void			ps_jobcont(t_job *job, int fg);
extern void			ps_jobdebug(t_job *job);

extern int			ps_procbilaunch(struct s_proc *proc);
extern int			ps_procbitlaunch(struct s_proc *proc);
extern int			ps_procerrlaunch(struct s_proc *prc);
extern int			ps_procexelaunch(struct s_proc *prc);
extern int			ps_procfnlaunch(struct s_proc *proc);

#endif
