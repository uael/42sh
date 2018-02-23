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

static inline int	srcctor(t_src *src, int fd, char **it, char **ln)
{
	if (!*it || !**it)
		return (NOP);
	src->fd = fd;
	src->it = it;
	src->ln = ln ? ln : it;
	return (YEP);
}

static inline void	promote(t_tok *prv, t_tok *tok, char const *ln)
{
	char const	*val = ln + tok->pos;

	if (!TOK_ISWORD(tok->id) || !(!prv || !TOK_ISCMDM(prv->id)))
		return ;
	if (tok->len == 1 && !ft_strncmp("!", val, 1))
		tok->id = TOK_BANG;
	if (tok->len == 2 && !ft_strncmp("if", val, 2))
		tok->id = TOK_IF;
	else if (tok->len == 4 && !ft_strncmp("then", val, 4))
		tok->id = TOK_THEN;
	else if (tok->len == 4 && !ft_strncmp("elif", val, 4))
		tok->id = TOK_ELIF;
	else if (tok->len == 4 && !ft_strncmp("else", val, 4))
		tok->id = TOK_ELSE;
	else if (tok->len == 2 && !ft_strncmp("fi", val, 2))
		tok->id = TOK_FI;
	else if (tok->len == 2 && !ft_strncmp("[[", val, 2))
		tok->id = TOK_DLBRA;
	else if (tok->len == 2 && !ft_strncmp("]]", val, 2))
		tok->id = TOK_DRBRA;
}

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

inline int			sh_lexline(t_src *src, t_deq *toks, t_bool new)
{
	int		st;
	t_tok	*tok;
	t_tok	*prv;
	size_t	cur;

	if (!**src->it)
	{
		st = NOP;
		if (!new || (src->fd < 0 ||
			(st = rl_catline(src->fd, 0, src->ln, src->it)) || !**src->it))
			return (st ? st : NOP);
	}
	cur = toks->cur;
	while (1)
	{
		ft_bzero(tok = (t_tok *)ft_deqpush(toks), sizeof(t_tok));
		if ((st = sh_tokenize(src, tok)))
			return (st);
		prv = toks->len > 1 ? ft_deqat(toks, toks->len - 2) : NULL;
		promote(prv, tok, *src->ln);
		if (TOK_ISEND(tok->id))
			return (sh_lexreduce(src, toks, cur));
	}
}

int					sh_lex(int fd, char **it, char **ln, t_lexcb *cb)
{
	t_src	src;
	t_deq	toks;

	if (srcctor(&src, fd, it, ln))
		return (NOP);
	ft_deqctor(&toks, sizeof(t_tok));
	while (!sh_lexline(&src, &toks, 0))
	{
		if (sh_lexcheck(&src, &toks))
			return (ft_dtor(NOP, (t_dtor)ft_deqdtor, &toks, NULL));
		if (cb(fd, &toks, src.ln))
			g_sh->status = 1;
	}
	return (NOP);
}
