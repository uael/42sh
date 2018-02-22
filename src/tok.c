/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/tok.h"

static char		*g_tokidsstr[] = {
	[TOK_END] = "<EOF>",
	[TOK_HEREDOC] = "<<",
	[TOK_RAOUT] = ">>",
	[TOK_LAMP] = "<&",
	[TOK_RAMP] = ">&",
	[TOK_CMP] = "<>",
	[TOK_EOL] = "<newline>",
	[TOK_RPOUT] = ">|",
	[TOK_AMPR] = "&>",
	[TOK_LAND] = "&&",
	[TOK_LOR] = "||",
	[TOK_WORD] = "<word>",
	[TOK_IF] = "if",
	[TOK_THEN] = "then",
	[TOK_ELIF] = "elif",
	[TOK_ELSE] = "else",
	[TOK_FI] = "fi",
	[TOK_AMP] = "&",
	[TOK_LPAR] = "(",
	[TOK_RPAR] = ")",
	[TOK_SEMICOLON] = ";",
	[TOK_RIN] = "<",
	[TOK_ROUT] = ">",
	[TOK_PIPE] = "|"
};

inline char		*sh_tokstr(t_tok *tok)
{
	char *ret;

	if (!tok)
		return (g_tokidsstr[TOK_END]);
	if (tok->id > TOK_PIPE)
		return ("<unknown>");
	return ((ret = g_tokidsstr[tok->id]) ? ret : "<unknown>");
}

inline t_tok	*sh_tokpeek(t_deq *toks)
{
	if (ft_deqlen(toks))
		return (ft_deqbeg(toks));
	return (NULL);
}

inline t_tok	*sh_toknext(t_deq *toks)
{
	ft_deqsht(toks, NULL);
	return (sh_tokpeek(toks));
}

inline void		sh_tokdtor(t_tok *tok)
{
	ft_memset(tok, 0, sizeof(t_tok));
}

inline t_tok	*sh_tokpos(t_tok *tok, char const *it, char const *ln)
{
	tok->pos = (uint16_t)(it - ln);
	return (tok);
}
