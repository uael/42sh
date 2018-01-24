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

#define UNEX "Unexpected token `%s'"

static t_map		g_binaries_stack =
{
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(char *), NULL, NULL
};
t_map				*g_binaries = &g_binaries_stack;

inline void			sh_evaldtor(void)
{
	ft_mapdtor(g_binaries, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
}

static int			parseeol(t_deq *toks, char **ln)
{
	t_tok *tok;

	while ((tok = sh_tokpeek(toks)))
		if (tok->id == TOK_EOL)
			ft_deqsht(toks, NULL);
		else if (tok->id == TOK_END)
			return (YEP);
		else
			return (sh_evalerr(*ln, tok, UNEX, sh_tokstr(tok)));
	return (YEP);
}

static inline int	evalfini(int ret, t_deq *toks, int fd)
{
	t_tok	*tok;

	sh_poolclean();
	if (fd < 0)
	{
		sh_varunscope();
		sh_poolunscope();
	}
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
		return (NOP);
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
	if (!(tok = sh_tokpeek(toks)))
		return (evalfini(YEP, toks, fd));
	while (tok && tok->id == TOK_EOL)
		tok = sh_toknext(toks);
	if (sh_evallist(fd, toks, ln) == OUF)
		return (evalfini(NOP, toks, fd));
	if (!(tok = sh_tokpeek(toks)))
		return (evalfini(YEP, toks, fd));
	if (tok->id == TOK_SEMICOLON)
		sh_toknext(toks);
	else if (tok->id == TOK_END)
		return (evalfini(YEP, toks, fd));
	else if (tok->id != TOK_EOL)
		return (evalfini(sh_evalerr(*ln, tok, UNEX, sh_tokstr(tok)), toks, fd));
	return (evalfini(parseeol(toks, ln), toks, fd));
}
