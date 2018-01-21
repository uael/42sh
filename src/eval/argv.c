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

inline int		sh_evalargv(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_vec	av;
	int		st;
	t_proc	*proc;

	(void)fd;
	tok = sh_tokpeek(toks);
	proc = ft_vecpush((t_vec *)&job->processes);
	ft_vecctor(&av, sizeof(char *));
	if ((st = sh_procctor(proc, "PATH", tok->val, g_env)))
	{
		sh_proccmderr(proc, *ln, tok, st);
		tok = sh_toknext(toks);
		while (tok && tok->id == TOK_WORD)
			tok = sh_toknext(toks);
	}
	else
	{
		*(char **)ft_vecpush(&av) = ft_strdup(tok->val);
		tok = sh_toknext(toks);
		while (tok && tok->id == TOK_WORD)
		{
			*(char **)ft_vecpush(&av) = ft_strdup(tok->val);
			tok = sh_toknext(toks);
		}
	}
	*(char **)ft_vecpush(&av) = NULL;
	proc->argv = av.buf;
	return (YEP);
}
