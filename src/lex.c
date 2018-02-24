/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"
#include "ush/shell.h"

inline int			sh_tokenize(t_src *s, t_tok *tok)
{
	int		st;

	while (1)
		if ((st = sh_lexbslash(s)))
			return (st);
		else if (**s->it && ft_strchr(sh_ifs(), **s->it))
			++*s->it;
		else if (ISEOL(*s->it))
			return (((sh_tokpos(tok, (*s->it)++, *s->ln)->id = '\n')) & 0);
		else if (**s->it == '#')
			while (**s->it && !ISEOL(*s->it))
				++*s->it;
		else if (!**s->it)
			return ((sh_tokpos(tok, *s->it, *s->ln)->id = TOK_END) & 0);
		else
			break ;
	sh_tokpos(tok, *s->it, *s->ln);
	ft_isdigit(**s->it) ? (void)(++tok->len && ++*s->it) : 0;
	return (((st = sh_lexop(s, tok)) != NOP ||
		(st = sh_lexword(s, tok)) != NOP) ? st :
		sh_synerr(*s->ln, *s->it, "Unexpected token `%c'", **s->it));
}

int					sh_lex(int fd, char **it, char **ln, t_lexcb *cb)
{
	t_src	src;
	t_deq	toks;
	int		st;

	if (!*it || !**it)
		return (NOP);
	src.fd = fd;
	src.it = it;
	src.ln = ln ? ln : it;
	ft_deqctor(&toks, sizeof(t_tok));
	while (!(st = sh_lexline(&src, &toks, 0)))
	{
		if (sh_lexcheck(&src, &toks))
		{
			g_sh->status = 1;
			return (ft_dtor(OUF, (t_dtor)ft_deqdtor, &toks, NULL));
		}
		if (cb(fd, &toks, src.ln))
			g_sh->status = 1;
	}
	if (st == OUF)
		g_sh->status = 1;
	return (ft_dtor(st, (t_dtor)ft_deqdtor, &toks, NULL));
}
