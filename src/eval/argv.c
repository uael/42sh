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
	t_proc	proc;

	(void)fd;
	(void)ln;
	tok = sh_tokpeek(toks);
	if ((st = sh_procctor(&proc, "PATH", tok->val, g_env)))
	{
		g_shstatus = st;
		if (st == PROC_NORIGHTS)
			return (sh_parseerr(*ln, tok, "%s: permission denied", tok->val));
		return (sh_parseerr(*ln, tok, "%s: Command not found", tok->val));
	}
	ft_vecctor(&av, sizeof(char *));
	*(char **)ft_vecpush(&av) = proc.kind == PROC_FN ? ft_strdup(tok->val) :
		proc.u.exe;
	tok = sh_toknext(toks);
	while (tok->id == TOK_WORD)
	{
		*(char **)ft_vecpush(&av) = ft_strdup(tok->val);
		tok = sh_toknext(toks);
	}
	*(char **)ft_vecpush(&av) = NULL;
	proc.argv = av.buf;
	ft_veccpush((t_vec *)&job->processes, &proc);
	return (YEP);
}
