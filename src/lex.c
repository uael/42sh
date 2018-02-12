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

#define UEE "parse error: Unexpected EOF while looking for matching `%c'"
#define UEC "parse error: Unexpected closing bracket `%c'"
#define UEH "syntax error: Expected `<word>' after heredoc `%s' got `%s'"
#define EXS "syntax error: Unexpected empty command between `%s'"

static int			g_sidx;

static inline int	lexctor(t_tokit *tit, char **it, char **ln, t_deq *d)
{
	if (!*it || !**it)
		return (NOP);
	!ln ? (ln = it) : 0;
	tit->it = it;
	tit->ln = ln;
	ft_deqctor(d, sizeof(t_tok));
	return (YEP);
}

static inline int	reduce(int fd, t_deq *toks, char **it, char **ln)
{
	t_tok *tok;
	t_tok *prev;
	t_tok *end;

	prev = NULL;
	tok = (t_tok *)ft_deqbeg(toks) - 1;
	end = ft_deqend(toks);
	while (++tok < end)
	{
		if (TOK_ISWORD(tok->id) && prev)
		{
			if (prev->id == TOK_HEREDOC && sh_lexheredoc(fd, tok, it, ln))
				return (OUF);
		}
		else if (prev && prev->id == TOK_HEREDOC)
			return (sh_synerr(*ln, *ln + tok->pos, UEH, sh_tokstr(prev),
				sh_tokstr(tok)));
		else if (prev && prev->id == tok->id && TOK_ISSEP(tok->id))
			return (sh_synerr(*ln, *ln + tok->pos, EXS, sh_tokstr(tok)));
		if ((prev = tok)->id == TOK_END || tok->id == TOK_EOL)
			break ;
	}
	return (YEP);
}

static inline int	check(int fd, t_tok *t, t_deq *deq, t_tokit *it)
{
	int st;

	if (TOK_ISEND(t->id))
	{
		if ((st = reduce(fd, deq, it->it, it->ln)))
			return (st);
		if (!g_sidx)
		{
			deq->cur = 0;
			return (NOP);
		}
		deq->cur = deq->len + 1;
	}
	else if (t->id == '(')
		++g_sidx;
	else if (g_sidx && t->id == ')')
		--g_sidx;
	else if (t->id == ')' && !g_sidx)
		return (sh_synerr(*it->ln, *it->ln + t->pos, UEC, t->id));
	return (YEP);
}

static inline int	tokenize(int fd, t_tok *tok, char **it, char **ln)
{
	int		st;

	while (1)
		if ((st = sh_lexbslash(fd, it, ln)))
			return (st);
		else if (**it && ft_strchr(sh_varifs(), **it))
			++*it;
		else if (ISEOL(*it))
			return (((sh_tokpos(tok, *it, *ln)->id = TOK_EOL) && ++*it) & 0);
		else if (**it == '#')
			while (**it && !ISEOL(*it))
				++*it;
		else if (!**it)
			return ((sh_tokpos(tok, *it, *ln)->id = TOK_END) & 0);
		else
			break ;
	sh_tokpos(tok, *it, *ln);
	ft_isdigit(**it) ? (++tok->len && ++*it) : 0;
	return (st = sh_lexop(fd, tok, it, ln)) != NOP ||
		(st = sh_lexword(fd, tok, it, ln)) != NOP ? st :
		sh_synerr(*ln, *it, "Unexpected token `%c'", **it);
}

int					sh_lex(int f, char **i, char **l, t_tokcb *cb)
{
	int		st;
	t_deq	*d;
	t_tok	*t;
	t_tokit	tit;

	if (lexctor(&tit, i, l, d = alloca(sizeof(t_deq))))
		return (NOP);
	d->buf = alloca((d->cap += 32) * sizeof(t_tok));
	while (1)
	{
		if (d->len == d->cap)
			d->buf = ft_memcpy(alloca((d->cap *= 2) * sizeof(t_tok)),
				d->buf, d->len * sizeof(t_tok));
		ft_memset(t = (t_tok *)d->buf + d->len++, 0, sizeof(t_tok));
		if ((st = tokenize(f, t, i, l)) || (st = check(f, t, d, &tit)))
		{
			if (st == NOP && cb(f, d, l))
				g_sh->status = 1;
			if (st == NOP && **i && !(d->len -= d->len) && !(d->cur -= d->cur))
				continue ;
			return (st);
		}
		if (g_sidx && !**i && (f < 0 || (st = rl_catline(f, 0, l, i)) || !**i))
			return (LEX_SHOWE(st, f) ? sh_synerr(*l, *i, UEE, ')') : OUF);
	}
}
