/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

static int	simplecommand(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	++*idx;
	while (*idx < toks->len)
	{
		tok = ft_deqat(toks, *idx);
		if (sh_tokis(tok, TOKS_WORD))
			++*idx;
		else if (!sh_tokis(tok, TOKS_REDIR))
			return (YEP);
		else if ((st = sh_synredir(s, toks, idx)))
			return (st);
	}
	return (YEP);
}

inline int	sh_syncmd(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	if (*idx >= toks->len)
		return (NOP);
	tok = ft_deqat(toks, *idx);
	if (tok->id == TOK_FUNCTION)
		return (sh_synfuncdef(s, toks, idx));
	if (sh_tokis(tok, TOKS_LEFT))
	{
		if ((st = sh_syncompoundcmd(s, toks, idx)))
			return (st);
		while (*idx < toks->len)
		{
			tok = ft_deqat(toks, *idx);
			if (!sh_tokis(tok, TOKS_REDIR))
				break ;
			if ((st = sh_synredir(s, toks, idx)))
				return (st);
		}
		return (YEP);
	}
	else if (sh_tokis(tok, TOKS_REDIR | TOKS_WORD))
		return (simplecommand(s, toks, idx));
	return (NOP);
}
