/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/compound.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

#define ERR0 "syntax error: Expected `%s' after `%s' got `%s'"

static int	openerr(t_src *s, t_deq *toks, size_t const *idx, size_t open)
{
	t_tok	*tok;
	t_tok	*tok2;

	tok = ft_deqat(toks, open);
	tok2 = *idx >= toks->len ? NULL : ft_deqat(toks, *idx);
	return (sh_evalerr(*s->ln, tok2, ERR0,
		"<compound_list>", sh_tokstr(tok), sh_tokstr(tok2)));
}

static int	compoundlist(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	sh_synlinebreak(toks, idx);
	if ((st = sh_synterm(s, toks, idx)))
		return (st);
	if (*idx >= toks->len)
		return (YEP);
	tok = ft_deqat(toks, *idx);
	if (tok->id == '&' || tok->id == ';')
		++*idx;
	sh_synlinebreak(toks, idx);
	return (YEP);
}

inline int	sh_syncompoundlist(t_src *s, t_deq *toks, size_t *idx,
	char const *stop)
{
	int		st;
	size_t	open;
	t_tok	*tok;

	open = (*idx)++;
	while (1)
	{
		if (*idx >= toks->len && (st = sh_lexline(s, toks, 1)))
			return (st != OUF ? openerr(s, toks, idx, open) : st);
		if ((st = compoundlist(s, toks, idx)) && st != NOP)
			return (st);
		if (*idx >= toks->len)
			continue ;
		tok = (t_tok *)ft_deqat(toks, *idx);
		if (ft_strchr(stop, tok->id))
			return (YEP);
		return (openerr(s, toks, idx, open));
	}
}

static int	compoundgrp(t_src *s, t_deq *toks, size_t *idx, uint8_t stop)
{
	int st;

	if ((st = sh_syncompoundlist(s, toks, idx, (char[]){stop, '\0'})))
		return (st);
	++*idx;
	return (YEP);
}

inline int	sh_syncompoundcmd(t_src *s, t_deq *toks, size_t *idx)
{
	t_tok *tok;

	tok = ft_deqat(toks, *idx);
	if (tok->id == '{')
		return (compoundgrp(s, toks, idx, '}'));
	else if (tok->id == '(')
		return (compoundgrp(s, toks, idx, ')'));
	else if (tok->id == TOK_IF)
		return (sh_synifclause(s, toks, idx));
	else if (tok->id == TOK_WHILE)
		return (sh_synwhileclause(s, toks, idx));
	else if (tok->id == TOK_UNTIL)
		return (sh_synwhileclause(s, toks, idx));
	else if (tok->id == TOK_FOR)
		return (sh_synforclause(s, toks, idx));
	return (NOP);
}
