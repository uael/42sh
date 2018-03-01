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

inline int	sh_synfuncdef(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;
	
	if (++*idx >= toks->len)
		return (NOP);
	if (!sh_tokis(tok = ft_deqat(toks, *idx), TOKS_WORD))
		return (NOP);
	if (!sh_isident(*s->ln + tok->pos, tok->len))
		return (NOP);
	if (++*idx >= toks->len)
		return (NOP);
	if (!sh_tokis(ft_deqat(toks, *idx), TOKS_LEFT))
		return (NOP);
	if ((st = sh_syncompoundcmd(s, toks, idx)))
		return (st);
	while (*idx < toks->len)
	{
		tok = ft_deqat(toks, *idx);
		if (!sh_tokis(tok, TOKS_REDIR))
			break ;
		++*idx;
	}
	return (YEP);
}
