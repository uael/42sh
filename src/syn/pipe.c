/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

#define ERR0 "syntax error: Expected `%s' after `%s' got `%s'"

static int	pipeerr(t_src *s, t_deq *toks, size_t const *idx, size_t pipe)
{
	t_tok	*tok;
	t_tok	*tok2;

	tok = ft_deqat(toks, pipe);
	tok2 = *idx >= toks->len ? NULL : ft_deqat(toks, *idx);
	return (sh_evalerr(*s->ln, tok2, ERR0,
		"<command>", sh_tokstr(tok), sh_tokstr(tok2)));
}

static int	pipesequence(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;
	size_t	pipe;

	if ((st = sh_syncmd(s, toks, idx)))
		return (st);
	while (*idx < toks->len)
	{
		tok = ft_deqat(toks, *idx);
		if (tok->id != '|' && tok->id != TOK_PIPEAND)
			return (YEP);
		pipe = (*idx)++;
		sh_synlinebreak(toks, idx);
		if ((st = sh_syncmd(s, toks, idx)))
			return (st == NOP ? pipeerr(s, toks, idx, pipe) : st);
	}
	return (YEP);
}

inline int	sh_synpipeline(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;
	size_t	bang;

	if (*idx >= toks->len)
		return (NOP);
	tok = ft_deqat(toks, *idx);
	bang = 0;
	if (sh_tokis(tok, TOKS_PREFIX))
	{
		bang = *idx;
		if (++*idx == toks->len)
			return (pipeerr(s, toks, idx, bang));
	}
	if ((st = pipesequence(s, toks, idx)) == NOP && bang)
		return (pipeerr(s, toks, idx, bang));
	return (st);
}
