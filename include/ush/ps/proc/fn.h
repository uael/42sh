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

# include <libft.h>

struct s_proc;

typedef int		(t_proccb)(void *data);

typedef struct	s_procfn
{
	t_proccb	*cb;
	t_dtor		dtor;
	void		*data;
}				t_procfn;

extern void		ps_procfn(struct s_proc *p, t_proccb *cb, t_dtor dtor, void *d);

#endif
