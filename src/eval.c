/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 13:39:06 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define UNEX "syntax error: Unexpected token `%s'"

static inline int	evalfini(int ret, t_deq *toks)
{
	t_tok	*tok;

	if (ret > 0)
	{
		tok = sh_tokpeek(toks);
		while (tok)
			if (tok->id != TOK_EOL && tok->id != TOK_END)
				tok = sh_toknext(toks);
			else
			{
				sh_toknext(toks);
				break ;
			}
	}
	toks->cur = toks->len;
	return (ret ? NOP : YEP);
}

inline int			sh_eval(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	int		st;

	st = 0;
	while (!st)
	{
		sh_evallinebreak(toks);
		if (!sh_tokpeek(toks))
			return (evalfini(YEP, toks));
		if ((st = sh_evallist(fd, toks, ln)) == OUF)
			return (evalfini(OUF, toks));
		if (!(tok = sh_tokpeek(toks)) || tok->id == TOK_END)
			return (evalfini(YEP, toks));
	}
	tok = sh_tokpeek(toks);
	return (evalfini(sh_evalerr(*ln, tok, UNEX, sh_tokstr(tok)), toks));
}
