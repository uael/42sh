/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok/expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/tok.h"

static t_tok		tokapd(uint16_t pos, char *beg, char *end)
{
	t_tok tok;

	ft_memset(&tok, 0, sizeof(t_tok));
	ft_sdsmpush((t_sds *)&tok, beg, end - beg);
	tok.id = TOK_WORD;
	tok.pos = pos;
	return (tok);
}

inline void			sh_tokexplode(t_tok *tok, t_deq *into)
{
	char		*val;
	char		*end;
	size_t		i;
	uint16_t	pos;

	while (tok->len && (ft_strchr(sh_varifs(), *tok->val) || ISREOL(tok->val)))
		ft_sdssht((t_sds *)tok, NULL);
	val = tok->val;
	while (*val && !ft_strchr(sh_varifs(), *val) && !ISREOL(val))
		++val;
	if (!*val || (*val = '\0'))
		return ;
	tok->len = val++ - tok->val;
	pos = tok->pos;
	i = 0;
	while (*val)
		if (ft_strchr(sh_varifs(), *val) || ISREOL(val))
			++val;
		else if (*(end = val))
		{
			while (*end && !ft_strchr(sh_varifs(), *end) && !ISREOL(end))
				++end;
			*(t_tok *)ft_deqput(into, ++i) = tokapd(pos, val, end);
			val = end;
		}
}

static inline void	tokswap(t_tok *a, t_tok *b)
{
	t_tok c;

	c = *a;
	*a = *b;
	*b = c;
}

static inline void	exroutine(t_tok **orig, t_deq *toks, int *ex, int *apd)
{
	t_tok *tok;

	tok = *orig;
	while (1)
	{
		if (((tok->spec & TSPEC_DQUOTE) || (tok->spec & TSPEC_SQUOTE)) && *ex)
			*ex = 0;
		tok->id == TOK_VAR && (*apd = 1) ? sh_wordexpand((t_sds *)tok) : 0;
		if (tok != *orig)
		{
			ft_sdsapd((t_sds *)*orig, tok->val);
			sh_tokdtor(tok);
			tokswap(tok, *orig);
			*orig = sh_toknext(toks);
		}
		if (ft_deqlen(toks) > 1)
		{
			tok = ft_deqat(toks, 1);
			if (!TOK_ISWORD(tok->id) || !(tok->spec & TSPEC_CONTINUOUS))
				break ;
		}
		else
			break ;
	}
}

inline t_tok		*sh_tokexpand(t_deq *toks, int explode)
{
	t_tok	*tok;
	int		apd;
	int		ex;

	ex = explode;
	if (!(tok = sh_tokpeek(toks)))
		return (NULL);
	apd = 0;
	exroutine(&tok, toks, &ex, &apd);
	if (ex && apd && tok->len)
	{
		sh_tokexplode(tok, toks);
		tok = sh_tokpeek(toks);
	}
	if (!explode || tok->len || (tok->spec & TSPEC_DQUOTE) ||
		(tok->spec & TSPEC_SQUOTE) || !TOK_ISWORD(tok->id))
		return (sh_tokpeek(toks));
	sh_toknext(toks);
	return (sh_tokexpand(toks, explode));
}
