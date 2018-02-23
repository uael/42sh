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

static inline void	promote2(t_tok *tok, char const *val)
{
	if (tok->len == 2 && !ft_strncmp("]]", val, 2))
		tok->id = TOK_DRBRA;
	else if (tok->len == 2 && !ft_strncmp("do", val, 2))
		tok->id = TOK_DO;
	else if (tok->len == 4 && !ft_strncmp("done", val, 4))
		tok->id = TOK_DONE;
	else if (tok->len == 5 && !ft_strncmp("while", val, 5))
		tok->id = TOK_WHILE;
}

static inline void	promote(t_tok *prv, t_tok *tok, char const *ln)
{
	char const	*val = ln + tok->pos;

	if (!TOK_ISWORD(tok->id))
		return ;
	else if (tok->len == 2 && !ft_strncmp("]]", val, 2))
		tok->id = TOK_DRBRA;
	else if (prv && TOK_ISCMDM(prv->id))
		return ;
	else if (tok->len == 1 && !ft_strncmp("!", val, 1))
		tok->id = TOK_BANG;
	else if (tok->len == 2 && !ft_strncmp("if", val, 2))
		tok->id = TOK_IF;
	else if (tok->len == 4 && !ft_strncmp("then", val, 4))
		tok->id = TOK_THEN;
	else if (tok->len == 4 && !ft_strncmp("elif", val, 4))
		tok->id = TOK_ELIF;
	else if (tok->len == 4 && !ft_strncmp("else", val, 4))
		tok->id = TOK_ELSE;
	else if (tok->len == 2 && !ft_strncmp("fi", val, 2))
		tok->id = TOK_FI;
	else if (tok->len == 2 && !ft_strncmp("[[", val, 2))
		tok->id = TOK_DLBRA;
	else
		return (promote2(tok, val));
}

inline int			sh_lexline(t_src *src, t_deq *toks, t_bool new)
{
	int		st;
	t_tok	*tok;
	t_tok	*prv;
	size_t	cur;

	if (!**src->it)
	{
		st = NOP;
		if (!new || (src->fd < 0 ||
			(st = rl_catline(src->fd, 0, src->ln, src->it)) || !**src->it))
			return (st ? st : NOP);
	}
	cur = toks->cur;
	while (1)
	{
		ft_bzero(tok = (t_tok *)ft_deqpush(toks), sizeof(t_tok));
		if ((st = sh_tokenize(src, tok)))
			return (st);
		prv = toks->len > 1 ? ft_deqat(toks, toks->len - 2) : NULL;
		promote(prv, tok, *src->ln);
		if (TOK_ISEND(tok->id))
			return (sh_lexreduce(src, toks, cur));
	}
}
