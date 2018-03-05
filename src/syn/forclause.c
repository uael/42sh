/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/forclause.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

#define ERR0 "syntax error: Expected `%s' after `%s' got `%s'"

static int	readerr(t_src *s, t_deq *toks, size_t const *idx, size_t open)
{
	t_tok	*tok;
	t_tok	*tok2;

	tok = ft_deqat(toks, open);
	tok2 = *idx >= toks->len ? NULL : ft_deqat(toks, *idx);
	return (sh_evalerr(*s->ln, tok2, ERR0,
		"<sequential_list>", sh_tokstr(tok), sh_tokstr(tok2)));
}

static int	readuntil(t_src *s, t_deq *toks, size_t *idx, char const *stop)
{
	int		st;
	size_t	open;
	t_tok	*tok;

	open = (*idx)++;
	while (1)
	{
		if (*idx >= toks->len && (st = sh_lexline(s, toks, 1)))
			return (st != OUF ? readerr(s, toks, idx, open) : st);
		sh_synlinebreak(toks, idx);
		if (*idx >= toks->len)
			continue ;
		tok = (t_tok *)ft_deqat(toks, *idx);
		if (ft_strchr(stop, tok->id))
			return (YEP);
		return (readerr(s, toks, idx, open));
	}
}

static int	wordlist(t_src *src, t_tok *tok, t_deq *toks, size_t *idx)
{
	while (++*idx < toks->len)
	{
		tok = ft_deqat(toks, *idx);
		if (!sh_tokis(tok, TOKS_WORD))
			break ;
	}
	if (tok->id != '\n' && tok->id != ';')
		return (NOP);
	return (readuntil(src, toks, idx, (char[]){TOK_DO, '\0'}));
}

inline int	sh_synforclause(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	if (++*idx >= toks->len)
		return (NOP);
	if (!sh_tokis(tok = ft_deqat(toks, *idx), TOKS_WORD))
		return (NOP);
	if (!sh_isident(*s->ln + tok->pos, tok->len))
		return (NOP);
	if ((st = readuntil(s, toks, idx, (char[]){TOK_IN, TOK_DO, '\0'})))
		return (st);
	tok = ft_deqat(toks, *idx);
	if (tok->id == TOK_IN && (st = wordlist(s, tok, toks, idx)))
		return (st);
	if ((st = sh_syncompoundlist(s, toks, idx,
		(char const[]){TOK_DONE, '\0'})))
		return (st);
	++*idx;
	return (YEP);
}
