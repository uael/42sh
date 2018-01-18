/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static int			parseeol(t_deq *toks, char **ln)
{
	t_tok *tok;

	while ((tok = sh_tokpeek(toks)))
		if (tok->id == TOK_EOL)
			ft_deqsht(toks, NULL);
		else if (tok->id == TOK_END)
			return (YEP);
		else
			return (sh_synerr(*ln, *ln + tok->pos, "2: Unexpected token `%s'",
				sh_tokidstr(tok->id)));
	return (YEP);
}

static inline int	evalfinalize(int ret, int fd)
{
	if (fd < 0)
	{
		sh_varunscope();
		sh_poolunscope();
	}
	return (ret);
}

inline int			sh_eval(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;

	if (fd < 0)
	{
		sh_varscope();
		sh_poolscope();
	}
	if (sh_evallist(fd, toks, ln))
		return (evalfinalize(NOP, fd));
	if (!(tok = sh_tokpeek(toks)))
		return (evalfinalize(YEP, fd));
	if (tok->id == TOK_SEMICOLON)
		sh_toknext(toks);
	else if (tok->id == TOK_END)
		return (evalfinalize(YEP, fd));
	else if (tok->id != TOK_EOL)
		return (evalfinalize(sh_synerr(*ln, *ln + tok->pos,
			"3: Unexpected token `%s'", sh_tokidstr(tok->id)), fd));
	return (evalfinalize(parseeol(toks, ln), fd));
}
