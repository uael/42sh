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

static t_tok	tokapd(t_tok *prev, char *beg, char *end)
{
	t_tok tok;

	ft_memset(&tok, 0, sizeof(t_tok));
	ft_sdsmpush((t_sds *)&tok, beg, end - beg);
	tok.id = TOK_WORD;
	tok.pos = prev->pos;
	return (tok);
}

inline void		sh_tokexplode(t_tok *tok, t_deq *into)
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

inline void		sh_tokexpand(t_tok *tok, t_deq *toks)
{
	if (*tok->val == '$' && tok->len > 1)
	{
		sh_wordexpand((t_sds *)tok);
		sh_tokexplode(tok, toks);
	}
}