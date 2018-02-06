/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libps/proc/exe.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPS_PROC_EXE_H
# define LIBPS_PROC_EXE_H

# include <libft.h>

# define PROC_NOTFOUND (127)
# define PROC_NORIGHTS (126)
# define PROC_ISDIR (1)

struct s_proc;

typedef struct	s_procexe
{
	char const	*pvar;
}				t_procexe;

extern void		ps_procexe(struct s_proc *ps, char const *p, char *e, char **v);
extern int		ps_procexelaunch(struct s_proc *prc);

#endif
