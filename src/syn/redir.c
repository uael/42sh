/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

#define ERR0 "syntax error: Expected `%s' after redirection `%s' got `%s'"

inline int	sh_synredir(t_src *src, t_deq *toks, size_t *idx)
{
	t_tok	*tok;
	t_tok	*op;

	op = ft_deqat(toks, *idx);
	tok = ++*idx >= toks->len ? NULL : ft_deqat(toks, *idx);
	if (!tok || !sh_tokis(tok, TOKS_WORD))
	{
		return (sh_evalerr(*src->ln, tok, ERR0,
			"<word>", sh_tokstr(op), sh_tokstr(tok)));
	}
	++*idx;
	return (YEP);
}
