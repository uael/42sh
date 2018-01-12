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

# include "shell.h"

typedef struct	s_proc
{
	struct s_proc	*next;
	char			**argv;
	pid_t			pid;
	t_bool			completed;
	t_bool			stopped;
	int				status;
}				t_proc;

extern void		sh_proclaunch(t_proc *p, pid_t pgid, int *io, int fg);
extern int		sh_procmark(pid_t pid, int status);
extern void		sh_procupdate(void);

#endif
