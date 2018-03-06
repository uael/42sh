/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

static inline int	opright(t_src *s, t_tok *tok)
{
	int st;

	if (++*s->it && (st = sh_lexbslash(s)))
		return (st);
	if (**s->it == '>' && ++*s->it)
		return ((tok->id = TOK_RAOUT) & 0);
	if (**s->it == '&' && ++*s->it)
		return ((tok->id = TOK_RAMP) & 0);
	return ((tok->id = '>') & 0);
}

static inline int	opleft(t_src *s, t_tok *tok)
{
	int st;

	if (++*s->it && (st = sh_lexbslash(s)))
		return (st);
	if (**s->it == '<')
	{
		if (++*s->it && (st = sh_lexbslash(s)))
			return (st);
		if (**s->it == '<' && ++*s->it)
			return ((tok->id = TOK_HERENOW) & 0);
		return ((tok->id = TOK_HEREDOC) & 0);
	}
	if (**s->it == '>' && ++*s->it)
		return ((tok->id = TOK_CMP) & 0);
	if (**s->it == '&' && ++*s->it)
		return ((tok->id = TOK_LAMP) & 0);
	return ((tok->id = '<') & 0);
}

static inline int	opand(t_src *s, t_tok *tok)
{
	int st;

	if (++*s->it && (st = sh_lexbslash(s)))
		return (st);
	if (**s->it == '&' && ++*s->it)
		return ((tok->id = TOK_LAND) & 0);
	if (**s->it == '>')
	{
		if (++*s->it && (st = sh_lexbslash(s)))
			return (st);
		if (**s->it == '>' && ++*s->it)
			return ((tok->id = TOK_AMPRA) & 0);
		return ((tok->id = TOK_AMPR) & 0);
	}
	return ((tok->id = '&') & 0);
}

static inline int	opor(t_src *s, t_tok *tok)
{
	int st;

	if (++*s->it && (st = sh_lexbslash(s)))
		return (st);
	if (**s->it == '|' && ++*s->it)
		return ((tok->id = TOK_LOR) & 0);
	if (**s->it == '&' && ++*s->it)
		return ((tok->id = TOK_PIPEAND) & 0);
	return ((tok->id = '|') & 0);
}

inline int			sh_lexop(t_src *s, t_tok *tok)
{
	if (**s->it == '>')
		return (opright(s, tok));
	if (**s->it == '<')
		return (opleft(s, tok));
	if (tok->len)
		return (NOP);
	if (**s->it == '&')
		return (opand(s, tok));
	if (**s->it == '|')
		return (opor(s, tok));
	if (**s->it == ';' && ++*s->it)
		return ((tok->id = TOK_SEMICOLON) & 0);
	if (**s->it == '(' && ++*s->it)
		return ((tok->id = TOK_LPAR) & 0);
	if (**s->it == ')' && ++*s->it)
		return ((tok->id = TOK_RPAR) & 0);
	return (NOP);
}
