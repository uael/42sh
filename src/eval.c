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

static t_map		g_binaries_stack =
{
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(char *), NULL, NULL
};
t_map				*g_binaries = &g_binaries_stack;

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

static inline int	evalfinalize(int ret, t_deq *toks, int fd)
{
	t_tok	*tok;

	if (fd < 0)
	{
		sh_varunscope();
		sh_poolunscope();
	}
	if (ret == NOP)
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
		return (NOP);
	if (!(tok = sh_tokpeek(toks)))
		return (evalfinalize(YEP, toks, fd));
	if (tok->id == TOK_SEMICOLON)
		sh_toknext(toks);
	else if (tok->id == TOK_END)
		return (evalfinalize(YEP, toks, fd));
	else if (tok->id != TOK_EOL)
		return (evalfinalize(sh_synerr(*ln, *ln + tok->pos,
			"Unexpected token `%s'", sh_tokidstr(tok->id)), toks, fd));
	return (evalfinalize(parseeol(toks, ln), toks, fd));
}
