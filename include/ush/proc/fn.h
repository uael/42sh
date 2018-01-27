/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/proc/fn.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PROC_FN_H
# define USH_PROC_FN_H

# include "../shell.h"

struct s_proc;

typedef int		(t_procfn)(int ac, char **av, char **envv);

extern void		sh_procfn(struct s_proc *proc, t_procfn *fn, char **envv);
extern int		sh_procfnlaunch(struct s_proc *proc);

#endif
