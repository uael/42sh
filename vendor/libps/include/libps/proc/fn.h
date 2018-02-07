/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libps/proc/fn.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPS_PROC_FN_H
# define LIBPS_PROC_FN_H

# include <libft.h>

struct s_proc;

typedef int		(t_proccb)(void *data);

typedef struct	s_procfn
{
	t_proccb	*cb;
	void		*data;
}				t_procfn;

extern void		ps_procfn(struct s_proc *proc, t_proccb *cb, void *data);

#endif
