/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static inline int	pipelineerr(int st, t_proc *p, t_deq *toks, char const *ln)
{
	t_tok	*tok;

	ps_procdtor(p);
	tok = sh_tokpeek(toks);
	return (st == NOP ? sh_evalerr(ln, tok, "Unexpected token `%s'"
		" on pipeline sequence", sh_tokstr(tok)) : st);
}

inline int			sh_evalpipeline(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_tok	*eol;
	t_proc	proc;
	int		st;

	ps_procctor(&proc);
	if ((st = sh_evalcmd(&proc, fd, toks, ln)))
		return (ft_dtor(st, (t_dtor)ps_procdtor, &proc, NULL));
	*(t_proc *)ft_vecpush((t_vec *)&job->procs) = proc;
	while (1)
		if (!(tok = sh_tokpeek(toks)))
			return (YEP);
		else if (tok->id == TOK_PIPE)
		{
			while ((eol = sh_toknext(toks)))
				if (eol->id != TOK_EOL)
					break ;
			ps_procctor(&proc);
			if ((st = sh_evalcmd(&proc, fd, toks, ln)))
				return (pipelineerr(st, &proc, toks, *ln));
			*(t_proc *)ft_vecpush((t_vec *)&job->procs) = proc;
		}
		else
			return (YEP);
}
