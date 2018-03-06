/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/funcdef.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

#define ERR0 "syntax error: Expected `%s' got `%s'"

inline int	sh_synfuncdef(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	if (++*idx >= toks->len)
		return (sh_evalerr(*s->ln, NULL, ERR0, "<name>", sh_tokstr(NULL)));
	if (!sh_tokis(tok = ft_deqat(toks, *idx), TOKS_WORD))
		return (sh_evalerr(*s->ln, tok, ERR0, "<word>", sh_tokstr(tok)));
	if (!sh_isident(*s->ln + tok->pos, tok->len))
		return (sh_evalerr(*s->ln, tok, ERR0, "<identifier>", sh_tokstr(tok)));
	if (++*idx >= toks->len)
		return (sh_evalerr(*s->ln, NULL, ERR0, "<body>", sh_tokstr(NULL)));
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
