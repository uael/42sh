/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static t_bool	isname(char *word)
{
	if (!ft_isalpha(*word) && *word != '_')
		return (0);
	++word;
	while (*word != '=')
	{
		if (!ft_isalnum(*word) && *word != '_')
			return (0);
		++word;
	}
	return (1);
}

inline int		sh_evalcommand(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	char	*assign;
	t_vec	av;
	int		st;
	t_proc	proc;

	(void)fd;
	(void)ln;
	if (!(tok = sh_tokpeek(toks)) || tok->id != TOK_WORD)
		return (NOP);
	while ((assign = ft_strchr(tok->val, '=')))
		if (assign == tok->val)
		{
			ft_sdssht((t_sds *)tok, NULL);
			break ;
		}
		else if (isname(tok->val))
		{
			*assign = '\0';
			sh_varset(tok->val, assign + 1);
			g_shstatus = 0;
			if (!(tok = sh_toknext(toks)) || tok->id != TOK_WORD)
				return (YEP);
		}
		else
			break ;
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
