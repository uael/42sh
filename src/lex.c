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
#include "ush/tok.h"

#define UEB "parse error: Unexpected token `%c' while looking for matching `%c'"
#define UEE "parse error: Unexpected EOF while looking for matching `%c'"
#define UEC "parse error: Unexpected closing bracket `%c'"

static char			g_stk[1000] = { 0 };
static int			g_sidx;

int					tokitctor(t_tokit *tit, char **it, char **ln)
{
	if (!*it || !**it)
		return (NOP);
	!ln ? (ln = it) : 0;
	tit->it = it;
	tit->ln = ln;
	return (YEP);
}

int					check(int fd, t_tok2 *t, t_deq *deq, t_tokit *it)
{
	int st;

	if (t->id == TOK_EOL || t->id == TOK_END)
	{
		if ((st = sh_lexreduce(fd, deq, it->it, it->ln)))
			return (st);
		if (!g_sidx)
		{
			deq->cur = 0;
			return (NOP);
		}
		deq->cur = deq->len + 1;
	}
	else if (ft_strchr("([{", t->id))
		g_stk[g_sidx++] = sh_rbracket(t->id);
	else if (g_sidx && t->id == g_stk[g_sidx - 1])
		--g_sidx;
	else if (ft_strchr(")}]", t->id) &&
		(!g_sidx || t->id != g_stk[g_sidx - 1]))
	{
		return (g_sidx ? sh_synerr(*it->ln, *it->ln + t->pos, UEB, t->id,
			g_stk[g_sidx - 1]) : sh_synerr(*it->ln, *it->ln + t->pos, UEC,
			t->id));
	}
	return (YEP);
}

static inline int	tokenize(int fd, t_tok2 *tok, char **it, char **ln)
{
	int		st;

	while (1)
		if ((st = sh_lexbslash(fd, it, ln)))
			return (st);
		else if (**it && ft_strchr(sh_varifs(), **it))
			++*it;
		else if (ISEOL(*it))
			return ((sh_tokpos(tok, ++*it, *ln)->id = TOK_EOL) & 0);
		else if (**it == '#')
			while (**it && !ISEOL(*it))
				++*it;
		else if (!**it)
			return ((sh_tokpos(tok, *it, *ln)->id = TOK_END) & 0);
		else
			break ;
	sh_tokpos(tok, *it, *ln);
	ft_isdigit(**it) ? ft_sdscpush((t_sds *)tok, *(*it)++) : 0;
	return (st = sh_lexop(fd, tok, it, ln)) != NOP ||
		(st = sh_lexword(fd, tok, it, ln)) != NOP ? st :
		sh_synerr(*ln, *it, "Unexpected token `%c'", **it);
}

int					sh_tokenize(int fd, char **it, char **ln, t_tokcb *cb)
{
	int		st;
	t_deq	*d;
	t_tok2	*t;
	t_tokit	tit;

	if (tokitctor(&tit, it, ln))
		return (NOP);
	ft_deqctor(d = alloca(sizeof(t_deq)), sizeof(t_tok2));
	d->buf += alloca((d->cap += 32) * sizeof(t_tok2));
	while (1)
	{
		if (d->len == d->cap)
		{
			t = alloca((d->cap *= 2) * sizeof(t_tok2));
			ft_memcpy(t, d->buf, d->len * sizeof(t_tok2));
			d->buf = t;
		}
		ft_memset(t = d->buf + d->len++, 0, sizeof(t_tok2));
		if ((st = tokenize(fd, t, it, ln)) || (st = check(fd, t, d, &tit)))
			return (st == NOP ? cb(fd, d, ln) : st);
		if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			return (st < 0 || !g_sh->tty ? sh_synerr(*ln, *it, UEE,
				g_stk[g_sidx - 1]) : OUF);
	}
}
