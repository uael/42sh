/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/reduce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

#define ERR9 "syntax error: Unexpected <heredoc> in subshell"

static inline int	hdocinsubshell(t_src *s, t_deq *toks)
{
	t_tok		*tok;
	t_tok		*end;
	uint16_t	depth;

	depth = 0;
	tok = (t_tok *)ft_deqbeg(toks) - 1;
	end = ft_deqend(toks);
	while (++tok < end)
	{
		if (tok->id == '(')
			++depth;
		else if (tok->id == ')' && depth)
			--depth;
		else if (tok->id == TOK_HEREDOC && depth)
			return (sh_synerr(*s->ln, *s->ln + tok->pos, ERR9));
	}
	return (YEP);
}

inline int			sh_lexreduce(t_src *s, t_deq *toks, size_t from)
{
	t_tok	*tok;
	t_tok	*prv;

	if (hdocinsubshell(s, toks))
		return (OUF);
	prv = NULL;
	while (from < toks->len)
	{
		tok = (t_tok *)ft_deqat(toks, from++);
		if (prv && sh_tokis(prv, TOKS_WORD) && tok->id == '(' &&
			from < toks->len && ((t_tok *)ft_deqat(toks, from))->id == ')')
		{
			ft_deqrem(toks, from, NULL);
			prv->id = TOK_FUNCTION;
			tok->id = TOK_WORD;
			tok->pos = prv->pos;
			tok->len = prv->len;
		}
		else if (sh_tokis(tok, TOKS_WORD) && prv && prv->id == TOK_HEREDOC)
			if (sh_lexheredoc(s, tok))
				return (OUF);
		if ((prv = tok)->id == TOK_END || tok->id == TOK_EOL)
			break ;
	}
	return (YEP);
}
