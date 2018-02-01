/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

static char			*g_tokidsstr[] =
{
	[TOK_END] = "<EOF>",
	[TOK_HEREDOC] = "<<",
	[TOK_HEREDOCT] = "<<-",
	[TOK_RAOUT] = ">>",
	[TOK_LAMP] = "<&",
	[TOK_RAMP] = ">&",
	[TOK_CMP] = "<>",
	[TOK_EOL] = "<newline>",
	[TOK_RPOUT] = ">|",
	[TOK_AMPR] = "&>",
	[TOK_LAND] = "&&",
	[TOK_LOR] = "||",
	[TOK_CASE] = "case",
	[TOK_DO] = "do",
	[TOK_DONE] = "done",
	[TOK_ELIF] = "elif",
	[TOK_ELSE] = "else",
	[TOK_FUNCTION] = "function",
	[TOK_FOR] = "for",
	[TOK_FI] = "fi",
	[TOK_IF] = "if",
	[TOK_IN] = "in",
	[TOK_ESAC] = "esac",
	[TOK_SELECT] = "select",
	[TOK_THEN] = "then",
	[TOK_UNTIL] = "until",
	[TOK_WHILE] = "while",
	[TOK_WORD] = "<word>",
	[TOK_NOT] = "!",
	[TOK_AMP] = "&",
	[TOK_LPAR] = "(",
	[TOK_RPAR] = ")",
	[TOK_HYPEN] = "-",
	[TOK_SEMICOLON] = ";",
	[TOK_RIN] = "<",
	[TOK_ASSIGN] = "=",
	[TOK_ROUT] = ">",
	[TOK_LBRACKET] = "[",
	[TOK_RBRACKET] = "]",
	[TOK_LCURLY] = "{",
	[TOK_PIPE] = "|",
	[TOK_RCURLY] = "}"
};

inline char			*sh_tokidstr(uint8_t id)
{
	char *ret;

	if (id > TOK_RCURLY)
		return ("<unknown>");
	return ((ret = g_tokidsstr[id]) ? ret : "<unknown>");
}

inline char			*sh_tokstr(t_tok *tok)
{
	char *ret;

	if (!tok)
		return (g_tokidsstr[TOK_END]);
	if (tok->id > TOK_RCURLY)
		return ("<unknown>");
	if (tok->len > 1)
		return (tok->val);
	return ((ret = g_tokidsstr[tok->id]) ? ret : "<unknown>");
}
