/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalsubshell(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_proc	proc;

	(void)fd;
	if (sh_procsh(&proc, toks, *ln))
		return (sh_evalerr(*ln, sh_tokpeek(toks), "Empty subshell"));
	sh_toknext(toks);
	ft_veccpush((t_vec *)&job->procs, &proc);
	return (YEP);
}
