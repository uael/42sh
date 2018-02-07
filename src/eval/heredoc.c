/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static inline int	output(char *data)
{
	ft_putf(STDOUT_FILENO, data);
	return (EXIT_SUCCESS);
}

static void			pipeprev(t_proc *prev, t_job *job, size_t i, char *out)
{
	t_proc *proc;

	if (i > 0 && (proc = job->procs.buf + i - 1)->u.fn.cb == output)
	{
		free(proc->u.fn.data);
		proc->u.fn.data = out;
		return ;
	}
	if (prev->kind == PROC_NONE)
			proc = prev;
	else
	{
		prev->piped = 1;
		proc = ft_vecput((t_vec *)&job->procs, i);
	}
	ps_procfn(proc, (t_proccb *)output, out);
}

inline int			sh_evalheredoc(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	size_t	i;
	t_tok	*op;
	t_proc	*proc;

	op = sh_tokpeek(toks);
	tok = sh_toknext(toks);
	i = job->procs.len - 1;
	proc = ft_vecat((t_vec *)&job->procs, i);
	if (ft_isdigit(*(*ln + op->pos)))
		proc->src[STDIN_FILENO] = *(*ln + op->pos) - '0';
	pipeprev(proc, job, i, ft_strndup(*ln + tok->pos, tok->pos));
	sh_toknext(toks);
	return (YEP);
}
