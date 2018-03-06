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
	[TOK_HERENOW] = "<<<",
	[TOK_RAOUT] = ">>",
	[TOK_LAMP] = "<&",
	[TOK_RAMP] = ">&",
	[TOK_CMP] = "<>",
	[TOK_EOL] = "<newline>",
	[TOK_PIPEAND] = "|&",
	[TOK_AMPR] = "&>",
	[TOK_LAND] = "&&",
	[TOK_LOR] = "||",
	[TOK_WORD] = "<word>",
	[TOK_ASSIGN] = "<word>",
	[TOK_BANG] = "!",
	[TOK_IF] = "if",
	[TOK_THEN] = "then",
	[TOK_ELIF] = "elif",
	[TOK_ELSE] = "else",
	[TOK_FI] = "fi",
	[TOK_WHILE] = "while",
	[TOK_UNTIL] = "until",
	[TOK_DO] = "do",
	[TOK_DONE] = "done",
	[TOK_FUNCTION] = "function",
	[TOK_FOR] = "for",
	[TOK_IN] = "in",
	[TOK_DLBRA] = "[[",
	[TOK_DRBRA] = "]]",
	[TOK_AMP] = "&",
	[TOK_LPAR] = "(",
	[TOK_RPAR] = ")",
	[TOK_SEMICOLON] = ";",
	[TOK_RIN] = "<",
	[TOK_ROUT] = ">",
	[TOK_PIPE] = "|",
	[TOK_LCUR] = "{",
	[TOK_RCUR] = "}",
};

static uint16_t		g_tokdef[UINT8_MAX] = {
	[TOK_END] = TOKS_END | TOKS_POSTFIX,
	[TOK_HEREDOC] = TOKS_REDIR,
	[TOK_HERENOW] = TOKS_REDIR,
	[TOK_RAOUT] = TOKS_REDIR,
	[TOK_LAMP] = TOKS_REDIR,
	[TOK_RAMP] = TOKS_REDIR,
	[TOK_CMP] = TOKS_REDIR,
	[TOK_EOL] = TOKS_END | TOKS_POSTFIX,
	[TOK_PIPEAND] = TOKS_OPERATOR,
	[TOK_AMPR] = TOKS_REDIR,
	[TOK_LAND] = TOKS_OPERATOR,
	[TOK_LOR] = TOKS_OPERATOR,
	[TOK_WORD] = TOKS_WORD,
	[TOK_ASSIGN] = TOKS_WORD,
	[TOK_BANG] = TOKS_PREFIX | TOKS_WORD,
	[TOK_IF] = TOKS_IDENT | TOKS_WORD | TOKS_LEFT,
	[TOK_THEN] = TOKS_IDENT | TOKS_WORD | TOKS_RIGHT,
	[TOK_ELIF] = TOKS_IDENT | TOKS_WORD | TOKS_RIGHT,
	[TOK_ELSE] = TOKS_IDENT | TOKS_WORD | TOKS_RIGHT,
	[TOK_FI] = TOKS_IDENT | TOKS_WORD | TOKS_RIGHT,
	[TOK_WHILE] = TOKS_IDENT | TOKS_WORD | TOKS_LEFT,
	[TOK_UNTIL] = TOKS_IDENT | TOKS_WORD | TOKS_LEFT,
	[TOK_DO] = TOKS_IDENT | TOKS_WORD | TOKS_RIGHT,
	[TOK_DONE] = TOKS_IDENT | TOKS_WORD | TOKS_RIGHT,
	[TOK_FUNCTION] = TOKS_IDENT | TOKS_WORD,
	[TOK_FOR] = TOKS_IDENT | TOKS_WORD | TOKS_LEFT,
	[TOK_IN] = TOKS_IDENT | TOKS_WORD | TOKS_RIGHT,
	[TOK_DLBRA] = TOKS_WORD,
	[TOK_DRBRA] = TOKS_WORD,
	[TOK_AMP] = TOKS_POSTFIX,
	[TOK_LPAR] = TOKS_LEFT,
	[TOK_RPAR] = TOKS_RIGHT,
	[TOK_SEMICOLON] = TOKS_POSTFIX,
	[TOK_RIN] = TOKS_REDIR,
	[TOK_ROUT] = TOKS_REDIR,
	[TOK_PIPE] = TOKS_OPERATOR,
	[TOK_LCUR] = TOKS_WORD | TOKS_LEFT,
	[TOK_RCUR] = TOKS_WORD | TOKS_RIGHT,
};

inline t_bool	sh_tokidis(uint8_t id, uint16_t flags)
{
	return ((t_bool)(g_tokdef[id] & flags));
}

inline t_bool	sh_tokis(t_tok *tok, uint16_t flags)
{
	if (!tok)
		return (0);
	return (sh_tokidis(tok->id, flags));
}

inline char		*sh_tokstr(t_tok *tok)
{
	char *ret;

	if (!tok)
		return (g_tokidsstr[TOK_END]);
	if (tok->id > TOK_RCUR)
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
