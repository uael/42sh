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

static inline void	promote(t_tok *tok, char const *ln)
{
	char const *val = ln + tok->pos;

	if (!tok->id != TOK_WORD)
		return ;
	if (tok->len == 2 && !ft_strcmp("if", val))
		tok->id = TOK_IF;
	else if (tok->len == 4 && !ft_strcmp("then", val))
		tok->id = TOK_THEN;
	else if (tok->len == 4 && !ft_strcmp("elif", val))
		tok->id = TOK_ELIF;
	else if (tok->len == 4 && !ft_strcmp("else", val))
		tok->id = TOK_ELSE;
	else if (tok->len == 2 && !ft_strcmp("fi", val))
		tok->id = TOK_FI;
}

inline int			sh_evalcmd(t_proc *proc, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	int		st;

	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	promote(tok, *ln);
	if (TOK_ISCMDM(tok->id))
		return (sh_evalsimple(proc, fd, toks, ln));
	else if (!(st = sh_evalcompound(proc, fd, toks, ln)))
	{
		while ((tok = sh_tokpeek(toks)))
			if (TOK_ISREDIR(tok->id))
			{
				if ((st = sh_evalredir(proc, toks, ln)))
					return (st);
			}
			else
				return (YEP);
	}
	return (st);
}
