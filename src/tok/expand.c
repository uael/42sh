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

static t_tok		tokapd(t_tok *prev, char *beg, char *end)
{
	t_tok tok;

	ft_memset(&tok, 0, sizeof(t_tok));
	ft_sdsmpush((t_sds *)&tok, beg, end - beg);
	tok.id = TOK_WORD;
	tok.pos = prev->pos;
	return (tok);
}

inline void			sh_tokexplode(t_tok *tok, t_deq *into)
{
	char	*val;
	char	*end;
	size_t	i;

	while (tok->len && ft_strchr(sh_varifs(), *tok->val))
		ft_sdssht((t_sds *)tok, NULL);
	val = tok->val;
	while (*val && !ft_strchr(sh_varifs(), *val))
		++val;
	if (!*val)
		return ;
	*val = '\0';
	tok->len = val++ - tok->val;
	i = 0;
	while (*val)
		if (ft_strchr(sh_varifs(), *val))
			++val;
		else if (*(end = val))
		{
			while (*end && !ft_strchr(sh_varifs(), *end))
				++end;
			*(t_tok *)ft_deqput(into, ++i) = tokapd(tok, val, end);
			val = end;
		}
}

static void			tokswap(t_tok *a, t_tok *b)
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
		if (tok->id == TOK_VAR && (*apd = 1))
			sh_wordexpand((t_sds *)tok);
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
	t_tok	*orig;
	int		apd;
	int		ex;

	ex = explode;
	if (!(orig = sh_tokpeek(toks)))
		return (NULL);
	apd = 0;
	exroutine(&orig, toks, &ex, &apd);
	if (ex && apd)
		sh_tokexplode(orig, toks);
	if (!explode || orig->len || (orig->spec & TSPEC_DQUOTE) ||
		(orig->spec & TSPEC_SQUOTE) || !TOK_ISWORD(orig->id))
		return (sh_tokpeek(toks));
	sh_toknext(toks);
	return (sh_tokexpand(toks, explode));
}
