/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glob.h>
#include "../ps.h"

static int		exhdl(int rcode, void *arg)
{
	(void)arg;
	errno = 0;
	return (rcode);
}

inline void		ps_biregister(char const *name, t_procbi *fn)
{
	uint32_t	it;
	char		*var;

	if (ft_mapput(g_builtins, var = ft_strdup(name), &it))
		((t_procbi **)g_builtins->vals)[it] = fn;
	else
		free(var);
}

inline int		ps_procbilaunch(t_proc *proc)
{
	t_ex_hdl	dfl;

	ft_exbind(EXALL, ft_exhdl(exhdl, NULL), &dfl);
	proc->status = proc->u.bi((int)proc->argv.gl_pathc, proc->argv.gl_pathv,
		proc->envv);
	ft_exbind(EXALL, dfl, NULL);
	if (proc->child)
	{
		ps_procdtor(proc);
		g_fatalcb(proc->status, NULL);
	}
	proc->state = PROC_COMPLETED;
	ft_dup2std(proc->scope, STD_FILENOS);
	return (YEP);
}
