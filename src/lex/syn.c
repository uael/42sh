/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/syn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

#define ERR0 "syntax error: Unexpected token `%s'"
#define ERR1 "syntax error: Expected `<word>' after redirection `%s' got `%s'"
#define ERR2 "syntax error: Expected `<command>' after `%s' got `%s'"
#define ERR3 "syntax error: Expected `<name>' after <function> got `%s'"
#define ERR4 "syntax error: Unexpected <EOF> after opening token `%s'"
#define ERR5 "syntax error: Unexpected opening token after `%s' got `%s'"
#define ERR7 "syntax error: Unexpected closing token after `%s' got `%s'"
#define ERR8 "syntax error: Unexpected token `%s' after `%s'"
#define ERR9 "syntax error: Expected compound command got `%s'"
#define ERRA "syntax error: Invalid identifier `%s'"

static char			*g_syn[UINT8_MAX] = {
	['('] = PAT(')'),
	['{'] = PAT('}'),
	[TOK_DLBRA] = PAT(TOK_DRBRA),
	[TOK_IF] = PAT(TOK_THEN),
	[TOK_WHILE] = PAT(TOK_DO),
	[TOK_THEN] = PAT(TOK_ELIF, TOK_ELSE, TOK_FI),
	[TOK_DO] = PAT(TOK_DONE),
	[TOK_ELIF] = PAT(TOK_THEN),
	[TOK_ELSE] = PAT(TOK_FI)
};

static inline size_t	bracketerr(t_src *s, char const *m, t_tok *o, t_tok *t)
{
	sh_synerr(*s->ln, t ? *s->ln + t->pos : NULL, m,
		sh_tokstr(o), sh_tokstr(t));
	return (0);
}

static inline int		synchk2(t_src *s, t_tok **a, t_tok *b)
{
	if (*a && (*a)->id == TOK_FUNCTION)
	{
		if (!TOK_ISWORD(b->id))
			return (sh_synerr(*s->ln, *s->ln + b->pos, ERR3, sh_tokstr(b)));
		if (!sh_isident(*s->ln + b->pos, b->len))
			return (sh_synerr(*s->ln, *s->ln + b->pos, ERRA, sh_tokstr(b)));
		if (TOK_ISWORD((b + 1)->id) && (b + 1)->len == 1 &&
			*(*s->ln + (b + 1)->pos) == '{')
			(b + 1)->id = TOK_LCUR;
		else if (!TOK_ISCMPD((b + 1)->id))
		{
			return (sh_synerr(*s->ln, *s->ln + (b + 1)->pos, ERR9,
				sh_tokstr(b)));
		}
	}
	*a = b;
	return (YEP);
}

inline int				sh_synchk(t_src *s, t_tok **a, t_tok *b)
{
	if (ft_strchr(TOKS_NOSOLO, b->id) && (!(*a) || !(TOK_ISWORD((*a)->id) ||
		ft_strchr(TOKS_CLOSE, (*a)->id))))
		return (sh_synerr(*s->ln, *s->ln + b->pos, ERR0, sh_tokstr(b)));
	if ((*a) && TOK_ISREDIR((*a)->id) && !TOK_ISWORD(b->id))
	{
		return (sh_synerr(*s->ln, *s->ln + b->pos, ERR1,
			sh_tokstr((*a)), sh_tokstr(b)));
	}
	if ((*a) && ft_strchr(TOKS_RVAL, (*a)->id) && !TOK_ISCMDM(b->id) &&
		!ft_strchr(TOKS_OPEN, b->id))
	{
		return (sh_synerr(*s->ln, *s->ln + b->pos, ERR2,
			sh_tokstr((*a)), sh_tokstr(b)));
	}
	if (b->id && (*a) && ft_strchr(TOKS_OPEN, b->id) &&
		!ft_strchr(TOKS_OPENPRV, (*a)->id))
	{
		return (sh_synerr(*s->ln, *s->ln + b->pos, ERR8,
			sh_tokstr(b), sh_tokstr((*a))));
	}
	return (synchk2(s, a, b));
}

static inline int		previsleft(t_tok *from, t_deq *toks)
{
	while (from->id == TOK_EOL)
	{
		if (from == (t_tok *)ft_deqbeg(toks))
			break ;
		--from;
	}
	return (TOK_ISLFT(from->id));
}

inline size_t			sh_synbracket(t_src *s, t_deq *toks, t_tok *o, size_t i)
{
	t_tok	*t;
	t_tok	*p;
	char	*syn;
	int		st;

	syn = g_syn[o->id];
	p = ft_deqat(toks, i);
	while (1)
		if (++i == toks->len && (st = sh_lexline(s, toks, 1)))
			return (st == OUF ? 0 : bracketerr(s, ERR4, o, NULL));
		else if (!(t = ft_deqat(toks, i)))
			return (bracketerr(s, ERR4, o, NULL));
		else if (ft_strchr(syn, t->id) && previsleft(p, toks))
			return (bracketerr(s, ERR5, o, t));
		else if (ft_strchr(syn, t->id))
			return (TOK_ISLFT(t->id) ? sh_synbracket(s, toks, t, i) : i);
		else if ((p = ft_deqat(toks, i - 1)) &&
			sh_synchk(s, &p, t = ft_deqat(toks, i)))
			return (0);
		else if (TOK_ISRGT(t->id))
			return (bracketerr(s, ERR7, o, t));
		else if (TOK_ISLFT(t->id) && !(i = sh_synbracket(s, toks, t, i)))
			return (0);
		else if ((t = ft_deqat(toks, i)) && TOK_ISLFT(t->id))
			p = ft_deqat(toks, i);
}
