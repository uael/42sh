/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalnewlines(t_deq *toks)
{
	t_tok *tok;

	if (!(tok = sh_tokpeek(toks)) || tok->id != TOK_EOL)
		return (NOP);
	while ((tok = sh_toknext(toks)) && tok->id == TOK_EOL)
		;
	return (YEP);
}

inline int		sh_evallinebreak(t_deq *toks)
{
	t_tok *tok;

	if (!sh_evalnewlines(toks))
		return (YEP);
	if (!(tok = sh_tokpeek(toks)) || tok->id == TOK_END)
		return (YEP);
	return (NOP);
}

inline int		sh_evalsepop(t_deq *toks)
{
	t_tok *tok;

	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	if (tok->id == TOK_SEMICOLON || tok->id == TOK_AMP)
	{
		sh_toknext(toks);
		return (YEP);
	}
	return (NOP);
}

inline int		sh_evalsep(t_deq *toks)
{
	t_tok *tok;

	if (!(tok = sh_tokpeek(toks)))
		return (YEP);
	if (tok->id == TOK_SEMICOLON || tok->id == TOK_AMP)
		return (sh_evalsepop(toks));
	return (sh_evallinebreak(toks));
}

inline int		sh_evalsepseq(t_deq *toks)
{
	t_tok *tok;

	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	if (tok->id == TOK_SEMICOLON)
	{
		sh_toknext(toks);
		return (sh_evallinebreak(toks));
	}
	return (sh_evalnewlines(toks));
}
