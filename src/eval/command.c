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
	if (!ft_isalpha(*word) || *word != '_')
		return (0);
	++word;
	while (*word != '=')
	{
		if (!ft_isalnum(*word) || *word != '_')
			return (0);
		++word;
	}
	return (1);
}

inline int		sh_evalcommand(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_proc	*proc;
	t_tok	*tok;
	char	*assign;
	t_vec	av;

	(void)fd;
	(void)ln;
	if (!(tok = sh_tokpeek(toks)) || tok->id != TOK_WORD)
		return (NOP);
	while ((assign = ft_strchr(tok->val, '=')))
		if (assign == tok->val)
			ft_sdssht((t_sds *)tok, NULL);
		else if (isname(tok->val))
		{
			*assign = '\0';
			sh_varset(tok->val, assign + 1);
			g_shstatus = 0;
			if (!(tok = sh_toknext(toks)) || tok->id != TOK_WORD)
				return (YEP);
		}
	ft_vecctor(&av, sizeof(char *));
	while (tok->id == TOK_WORD)
	{
		*(char **)ft_vecpush(&av) = tok->val;
		tok = sh_toknext(toks);
	}
	*(char **)ft_vecpush(&av) = NULL;
	proc = ft_vecpush((t_vec *)&job->processes);
	sh_procctor(proc);
	proc->argv = av.buf;
	proc->envv = g_env;
	return (YEP);
}
