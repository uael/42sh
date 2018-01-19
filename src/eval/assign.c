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

inline int		sh_evalassign(t_deq *toks)
{
	t_tok	*tok;
	char	*assign;
	int		st;

	st = NOP;
	tok = sh_tokpeek(toks);
	while ((assign = ft_strchr(tok->val, '=')))
		if (assign == tok->val)
		{
			ft_sdssht((t_sds *)tok, NULL);
			break ;
		}
		else if (isname(tok->val))
		{
			st = YEP;
			*assign = '\0';
			sh_varset(tok->val, assign + 1);
			g_shstatus = 0;
			if (!(tok = sh_toknext(toks)) || tok->id != TOK_WORD)
				break ;
		}
		else
			break ;
	return (st);
}
