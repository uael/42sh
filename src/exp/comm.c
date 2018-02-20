/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/comm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "ush/shell.h"
#include "ush/eval.h"
#include "ush/exp.h"

static int	expcommchild(char *ln)
{
	t_scope	*sh;
	int		st;
	char	*it;

	sh = g_sh;
	sh_scope();
	ft_memcpy(g_sh, sh, sizeof(t_scope));
	it = ln;
	while (!sh_lex(-1, &it, &ln, sh_eval))
		;
	st = g_sh->status;
	sh_unscope();
	return (st);
}

static void	onquote(int *quoted, char quote)
{
	if (quote == '\'')
	{
		if (*quoted == 0)
			*quoted = 1;
		else if (*quoted == 1)
			*quoted = 0;
	}
	else if (quote == '"')
	{
		if (*quoted == 0)
			*quoted = 2;
		else if (*quoted == 2)
			*quoted = 0;
	}
}

int			sh_expcomm(t_sds *word, char **words, t_vec *av)
{
	int		quoted;
	int		depth;
	t_sds	comm;

	depth = 1;
	quoted = 0;
	ft_sdsctor(&comm);
	while (**words)
	{
		if (**words == '\'' || **words == '"')
			onquote(&quoted, **words);
		else if (**words == ')')
		{
			if (!quoted && --depth == 0)
			{
				if (comm.len)
					return (sh_expcommexec(word, &comm, av));
			}
		}
		else if (**words == ')' && !quoted)
			++depth;
		*ft_sdspush(&comm) = **words;
		++*words;
	}
	return (42);
}

int			sh_expcommexec(t_sds *word, t_sds *comm, t_vec *av)
{
	t_proc	proc;
	int		fds[2];
	int		io[3];
	int		status;

	if (!comm->len)
		return (0);
	ps_procfn(&proc, (t_proccb *)expcommchild, (t_dtor)free, comm->buf);
	ft_memcpy(io, STD_FILENOS, 3 * sizeof(int));
	if (pipe(fds) < 0)
		sh_exit(THROW(WUT), NULL);
	io[STDOUT_FILENO] = fds[1];
	proc.close = fds[0];
	proc.child = 1;
	if (ps_procfork(&proc, NULL, io, 1))
		return (YEP);
	waitpid(-proc.pid, &status, WUNTRACED);
	close(fds[1]);
	sh_expcommread(fds[0], word, av);
	close(fds[0]);
	ps_procdtor(&proc);
	return (YEP);
}
