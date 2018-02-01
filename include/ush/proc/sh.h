/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/proc/sh.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PROC_SH_H
# define USH_PROC_SH_H

# include "../shell.h"

struct s_proc;

typedef struct	s_procsh
{
	t_deq		toks;
}				t_procsh;

extern void		sh_procsh(struct s_proc *proc);
extern int		sh_procshlaunch(struct s_proc *proc);

#endif
