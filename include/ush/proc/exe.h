/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/proc/exe.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PROC_EXE_H
# define USH_PROC_EXE_H

# include "../shell.h"

# define PROC_NOTFOUND (127)
# define PROC_NORIGHTS (126)

struct s_proc;

typedef char	*t_procexe;

extern int		sh_procexe(struct s_proc *proc, char *p, char *e, char **envv);
extern int		sh_procexelaunch(struct s_proc *prc);

#endif
