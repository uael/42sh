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

static inline int	ouput(int ac, char **av, char **envv)
{
	(void)ac;
	(void)envv;
	ft_putf(STDOUT_FILENO, av[0]);
	return (EXIT_SUCCESS);
}

static void			pipeprev(t_tok *tok, t_proc *prev, t_job *job, size_t i)
{
	t_proc *proc;

	if (prev->kind == PROC_NONE)
		proc = prev;
	else
	{
		prev->piped = 1;
		proc = ft_vecput((t_vec *)&job->procs, i);
	}
	sh_procfn(proc, ouput, NULL);
	proc->argv = ft_malloc(2 * sizeof(char **));
	proc->argv[0] = ft_strdup(tok->val);
	proc->argv[1] = NULL;
}

inline int			sh_evalheredoc(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	size_t	i;
	t_tok	*op;
	t_proc	*proc;

	(void)ln;
	op = sh_tokpeek(toks);
	tok = sh_toknext(toks);
	i = job->procs.len - 1;
	proc = ft_vecat((t_vec *)&job->procs, i);
	if (ft_isdigit(*op->val))
		proc->src[STDIN_FILENO] = *op->val - '0';
	if (i > 0 && job->procs.buf[i - 1].u.fn == ouput)
	{
		free(job->procs.buf[i - 1].argv[0]);
		job->procs.buf[i - 1].argv[0] = ft_strdup(tok->val);
	}
	else
		pipeprev(tok, proc, job, i);
	sh_toknext(toks);
	return (YEP);
}
