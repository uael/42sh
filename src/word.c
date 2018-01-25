/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/word.h"
#include "ush/lex.h"
#include "ush/tok.h"

static void		expandvar(t_sds *word)
{
	char		*var;
	char		*end;
	t_bool		bracket;

	var = word->buf + 1;
	if ((bracket = (t_bool)(*var == '{')))
		++var;
	end = var;
	while (*end)
	{
		if (bracket && *end == '}')
			break ;
		++end;
	}
	*end = '\0';
	word->len = 0;
	if ((end = sh_varget(var)))
		ft_sdsapd(word, end);
	else
		*word->buf = '\0';
}

/*
** TODO(42sh): Handle pathname expansion, glob
** https://github.com/uael/21sh/issues/29
*/

inline void		sh_wordglob(t_sds *word)
{
	(void)word;
}

static t_bool	isname(char *word)
{
	if (!ft_isalpha(*word) && *word != '_')
		return (0);
	++word;
	while (*word)
	{
		if (!ft_isalnum(*word) && *word != '_')
			return (0);
		++word;
	}
	return (1);
}

inline void		sh_wordexpand(t_sds *word)
{
	if (*word->buf == '$' && word->len > 1 && isname(word->buf + 1))
		expandvar(word);
}

inline void		sh_tokexpand(t_tok *tok, t_deq *toks)
{
	if (*tok->val == '$' && tok->len > 1 && isname(tok->val + 1))
	{
		sh_wordexpand((t_sds *)tok);
		sh_tokexplode(tok, toks);
	}
}
