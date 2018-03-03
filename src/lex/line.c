/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"


inline int			sh_lexline(t_src *src, t_deq *toks, t_bool new)
{
	int		st;
	t_tok	*tok;
	size_t	cur;

	if (!**src->it)
	{
		st = NOP;
		if (!new || (src->fd < 0 ||
			(st = rl_catline(src->fd, 0, src->ln, src->it)) || !**src->it))
			return (st ? st : NOP);
	}
	cur = toks->len;
	while (1)
	{
		ft_bzero(tok = (t_tok *)ft_deqpush(toks), sizeof(t_tok));
		if ((st = sh_tokenize(src, tok)))
			return (st);
		if (sh_tokis(tok, TOKS_END))
			return (sh_lexreduce(src, toks, cur));
	}
}
