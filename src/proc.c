/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/proc.h"

inline void		sh_procctor(t_proc *proc)
{
	ft_memset(proc, 0, sizeof(t_proc));
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	proc->io[STDIN_FILENO] = STDIN_FILENO;
	proc->io[STDOUT_FILENO] = STDOUT_FILENO;
	proc->io[STDERR_FILENO] = STDERR_FILENO;
}

inline void		sh_procdtor(t_proc *proc)
{
	ft_vecdtor((t_vec *)&proc->redirs, NULL);
}
